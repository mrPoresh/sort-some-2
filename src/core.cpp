#include "../inc/core.hh"


void Core::readFileInMemory(const std::string& filePath, int maxLines, Object<Variant>* object) {
    std::ifstream inputFileStream(filePath);

    if (inputFileStream) {
        std::string line;
        std::string headerLine;
        int lineCount = 0;

        std::getline(inputFileStream, headerLine);          // dont forget about header line!
        std::stringstream _ss(headerLine);
        std::string headerValue;

        while (std::getline(inputFileStream, line) && lineCount < maxLines) {
            std::stringstream ss(line);
            std::string value;
            Vector<Variant>* data = new Vector<Variant>();

            while (ss >> value) {
                if (value.find(".") != std::string::npos) {
                    try {
                        double d = std::stod(value);
                        data->pushBack(d);
                        //std::cout << "Got double value: " << d << '\n';
                        continue;
                    } catch (std::invalid_argument&) {
                        int i = std::stoi(value);
                        data->pushBack(i);
                        //std::cout << "Got int value: " << i << '\n';
                    };
                };

                try {
                    int i = std::stoi(value);
                    data->pushBack(i);
                    //std::cout << "Got int value: " << i << '\n';
                } catch (std::invalid_argument&) {
                    data->pushBack(value);
                    //std::cout << "Got string value: " << value << '\n';
                };
            };

            object->pushVector(new Vector<Variant>(std::move(*data)));

            delete data;
            lineCount++;
        };

        inputFileStream.close();
    } else {
        std::cerr << "Error: could not open file \"" << filePath << "\"" << std::endl;
        return;
    };
};

void Core::writeDataInFile(const std::string& filePath, Object<Variant>* object) {
    std::ofstream outputFileStream(filePath);

    if (outputFileStream) {

        do {
            Vector<Variant>* data = object->popVector();

            for (auto item = data->begin(); item != data->end(); ++item) {
                if (std::holds_alternative<std::string>(*item)) {
                    outputFileStream << std::get<std::string>(*item) << " ";
                } else if (std::holds_alternative<int>(*item)) {
                    outputFileStream << std::get<int>(*item) << " ";
                } else if (std::holds_alternative<double>(*item)) {
                    outputFileStream << std::get<double>(*item) << " ";
                }
            }

            outputFileStream << "\n";

            delete data;
        } while (!(object->size() == 0));    

        outputFileStream.close();
    } else {
        std::cerr << "Error: unable to open output file \"" << filePath << "\"" << std::endl;
        return;
    };
};

