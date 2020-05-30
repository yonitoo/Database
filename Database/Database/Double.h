#ifndef DOUBLE_H
#define DOUBLE_H

#include "ColumnType.h"
#include <vector>

class Double : public ColumnType
{
    private:
        void copy(const Double&);
        void erase();

    public:
        Double();
        Double(const std::string&, const std::vector<std::string>&);
        Double& operator=(const Double&);
        virtual ~Double();

        virtual void setValueAt(const unsigned int, const std::string&) override;
        virtual std::string getValueAt(const unsigned int) const override;
        virtual unsigned int getSize() const override;
        virtual void addElement(const std::string&) override;
        virtual std::string toString() const override;
};

#endif
