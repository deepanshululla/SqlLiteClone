#include "DataRow.h"

namespace SQLCore {

    DataRow::DataRow(uint32_t uniqueId, const std::string& username, const std::string& email) :d_id(uniqueId), d_username(username), d_email(email){

    }
    DataRow::operator std::string() const {
        return "DataRow(" + std::to_string(d_id)+","+d_email+","+d_username + ")";
    }
}