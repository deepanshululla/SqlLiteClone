#include <fstream>
#include "Serializer.h"


namespace SQLCore {
    template<class T, class Id>
    template<typename U, typename V>
    BinarySerializer<T, Id>::BinarySerializer(const BinarySerializer<U, V> &other) :d_fileDirectory(
            other.d_fileDirectory) {

    }

    template<class T, typename Id>
    BinarySerializer<T, Id>::BinarySerializer(const std::string &fileDirectory) :d_fileDirectory(fileDirectory) {

    }

    template<class T, typename Id>
    bool BinarySerializer<T, Id>::deserialize(std::shared_ptr<T> &data, Id id) const {
        std::string fileName;
        getFileName(id, fileName);
        // Input file stream. You might use string streams as well.
        {
            std::ifstream ifs(fileName, std::ios::binary);
            cereal::BinaryInputArchive iarchive(ifs);  // Choose binary format, reading direction.
            iarchive(data);
            ifs.close();
        }


        return true;

    }

    template<class T, class Id>
    bool BinarySerializer<T, Id>::serialize(std::shared_ptr<T> data, Id id) const {
        std::string fileName;
        getFileName(id, fileName);
        {
            std::ofstream ofs(fileName, std::ios::binary);  // Output file stream.
            cereal::BinaryOutputArchive oarchive(ofs); // Choose binary format, writingdirection.
            oarchive(data); // Save the modified instance.
            ofs.close();
        }
        return true;
    }

    template<class T, class Id>
    void BinarySerializer<T, Id>::getFileName(Id id, std::string &fileName) const {
        fileName = d_fileDirectory + "/" + std::to_string(id) + ".bin";
    }

    std::shared_ptr<Serializer<Page, int>> getSerializer(const std::string &fileDirectory) {
        return std::shared_ptr<BinarySerializer<Page, int>>(new BinarySerializer<Page, int>(fileDirectory));
    }

    int getFileId(std::string &fileName) {
        std::vector<std::string> splitVector;
        Utilities::Utils::split(fileName, (std::string &) ".", splitVector);
        return std::stoi(splitVector[0]);
    }

}