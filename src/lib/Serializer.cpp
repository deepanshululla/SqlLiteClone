#include <fstream>
#include "Serializer.h"


namespace SQLCore {

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
            if (!(ifs.good())) {
                ifs.close();
                return false;
            }
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
    auto BinarySerializer<T, Id>::conv_to_string(Id val) const {
        if constexpr (std::is_same<Id, std::string>::value)
        {
            return static_cast<std::string>(val);
        }
        else
        {
            return std::to_string(val);
        }
    }

    template<class T, class Id>
    void BinarySerializer<T, Id>::getFileName(Id id, std::string &fileName) const {
        std::string myId = conv_to_string(id);
        fileName = d_fileDirectory + "/" + myId + ".bin";
    }

    std::shared_ptr<Serializer<Page, int>> getSerializer(const std::string &fileDirectory) {
        return std::make_shared<BinarySerializer<Page, int>>(fileDirectory);
    }

    int getFileId(std::string &fileName) {
        std::vector<std::string> splitVector;
        Utilities::Utils::split(fileName, (std::string &) ".", splitVector);
        return std::stoi(splitVector[0]);
    }

    std::shared_ptr<Serializer<MetaDataStore, std::string>> getMetaDataSerializer(const std::string &fileDirectory) {
        return std::make_shared<BinarySerializer<MetaDataStore, std::string>>(fileDirectory);
    }

}