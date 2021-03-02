#ifndef SQLLITECLONE_DATAROW_H
#define SQLLITECLONE_DATAROW_H

#include <string>
#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>




namespace SQLCore {
    class DataRow {
    public:
        DataRow(uint32_t id, const std::string& username, const std::string& email);
        explicit operator std::string() const;
        template<class Archive>
        void serialize(Archive & archive)
        {
            archive(d_id, d_username, d_email);  // Simply list all the fields to be serialized/deserialized.
        }
        template <class Archive>
        static void load_and_construct( Archive & ar, cereal::construct<DataRow> & construct )
        {
            uint32_t id;
            std::string username;
            std::string email;
            ar(id, username, email);
            construct( id, username, email );
        }
    private:
        uint32_t d_id;
        std::string d_username;
        std::string d_email;
    };

}

#endif //SQLLITECLONE_DATAROW_H
