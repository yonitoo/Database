#ifndef INTEGER_H
#define INTEGER_H

#include "ColumnType.h"
#include <vector>

class Integer : public ColumnType
{
    private:
        void copy(const Integer&);
        void erase();

    public:
        Integer();
        Integer(const std::string&, const std::vector<std::string>&);
        Integer& operator=(const Integer&);
        virtual ~Integer();

        virtual void setValueAt(const unsigned int, const std::string&) override;
        virtual std::string getValueAt(const unsigned int) const override;
        virtual unsigned int getSize() const override;
        virtual void addElement(const std::string&) override;

        virtual void print(std::ostream&) const override;
        virtual bool read(std::istream&) override;
        virtual std::string toString() const override;
};

#endif // INTEGER_H
