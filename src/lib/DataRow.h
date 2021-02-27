#ifndef SQLLITECLONE_DATAROW_H
#define SQLLITECLONE_DATAROW_H

#include "string"

namespace SQLCore {
    const int COLUMN_USERNAME_SIZE=255;
    const int COLUMN_EMAIL_SIZE=255;
    typedef struct {
        uint32_t id;
        char username[COLUMN_USERNAME_SIZE];
        char email[COLUMN_EMAIL_SIZE];
    } Row;

    class DataRow {
    public:
        DataRow(uint32_t id, std::string username, std::string email);
        explicit operator std::string() const;
    private:
        uint32_t d_id;
        std::string d_username;
        std::string d_email;
    };

}

#endif //SQLLITECLONE_DATAROW_H
