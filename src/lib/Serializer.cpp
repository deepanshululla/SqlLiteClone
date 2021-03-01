#include <fstream>
#include "Serializer.h"


namespace SQLCore{
    template <class T>
    BinarySerializer<T>::BinarySerializer(const std::string& fileName) :d_fileName(fileName){

    }
    template <class T>
    bool BinarySerializer<T>::deserialize(T data) const {
        std::ifstream ifs(d_fileName);  // Input file stream. You might use string streams as well.

        cereal::BinaryInputArchive iarchive(ifs);  // Choose binary format, reading direction.
        iarchive(data);
        ifs.close();
        return true;

    }
    template <class T>
    bool BinarySerializer<T>::serialize(T data) const {
        std::ofstream ofs(d_fileName, std::ios_base::app);  // Output file stream.
        cereal::BinaryOutputArchive oarchive(ofs); // Choose binary format, writingdirection.
        oarchive(data); // Save the modified instance.
        ofs.close();

        return true;
    }

    template<class T>
    template<typename U>
    BinarySerializer<T>::BinarySerializer(const BinarySerializer<U> &other) :d_fileName(other.d_fileName){

    }

    std::shared_ptr<Serializer<DataRow>> getSerializer(const std::string& fileName) {
        return std::shared_ptr<BinarySerializer<DataRow>>(new BinarySerializer<DataRow>(fileName));
    }

}