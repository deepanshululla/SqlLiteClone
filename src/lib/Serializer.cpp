#include <fstream>
#include "Serializer.h"


namespace SQLCore{




    template<class T>
    template<typename U>
    BinarySerializer<T>::BinarySerializer(const BinarySerializer<U> &other) :d_fileName(other.d_fileName){

    }



    template <class T>
    BinarySerializer<T>::BinarySerializer(const std::string& fileName) :d_fileName(fileName){

    }
    template <class T>
    bool BinarySerializer<T>::deserialize(std::shared_ptr<T>& data) const {
        std::ifstream ifs(d_fileName, std::ios::binary);  // Input file stream. You might use string streams as well.
        {
            cereal::BinaryInputArchive iarchive(ifs);  // Choose binary format, reading direction.
            iarchive(data);
        }

        ifs.close();
        return true;

    }
    template <class T>
    bool BinarySerializer<T>::serialize(std::shared_ptr<T>& data) const {
        std::ofstream ofs(d_fileName, std::ios::binary);  // Output file stream.
        {
            cereal::BinaryOutputArchive oarchive(ofs); // Choose binary format, writingdirection.
            oarchive(data); // Save the modified instance.
        }

        ofs.close();

        return true;
    }



    std::shared_ptr<Serializer<Page>> getSerializer(const std::string& fileName) {
        return std::shared_ptr<BinarySerializer<Page>>(new BinarySerializer<Page>(fileName));
    }
    std::shared_ptr<Serializer<DataRow>> getRowSerializer(const std::string& fileName) {
        return std::shared_ptr<BinarySerializer<DataRow>>(new BinarySerializer<DataRow>(fileName));
    }

}