#ifndef STRING_H
#define STRING_H

#include "ColumnType.h"
#include <vector>
#include <string>

class String : public ColumnType
{
    private:
        void copy(const String&);
        void erase();

    public:
        String();
        String(const std::string&, const std::vector<std::string>&);
        String& operator=(const String&);
        virtual ~String();

        virtual void setValueAt(const unsigned int, const std::string&) override;
        virtual std::string getValueAt(const unsigned int) const override;
        virtual unsigned int getSize() const override;
        virtual void addElement(const std::string&) override;
        virtual std::string toString() const override;
};

#endif

