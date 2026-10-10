// Solution for ACMOJ 1073

#include <iostream>
using namespace std;

class Date {
private:
    int _year, _month, _day;
    static bool isLeap(int y) {
        return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
    }
    static int monthDays(int y, int m) {
        static const int mdays[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if (m == 2) return isLeap(y) ? 29 : 28;
        return mdays[m];
    }
    // days since 1900-01-01 (0 based)
    long toOrdinal() const {
        long days = 0;
        for (int y = 1900; y < _year; ++y) {
            days += isLeap(y) ? 366 : 365;
        }
        for (int m = 1; m < _month; ++m) {
            days += monthDays(_year, m);
        }
        days += _day - 1; // because 1900-01-01 is day 0
        return days;
    }
    void fromOrdinal(long ord) {
        int y = 1900;
        while (true) {
            int yearDays = isLeap(y) ? 366 : 365;
            if (ord >= yearDays) { ord -= yearDays; ++y; }
            else break;
        }
        int m = 1;
        while (true) {
            int md = monthDays(y, m);
            if (ord >= md) { ord -= md; ++m; }
            else break;
        }
        int d = (int)ord + 1;
        _year = y; _month = m; _day = d;
    }
    bool valid(int y, int m, int d) const {
        if (y < 1900 || y > 2030) return false;
        if (m < 1 || m > 12) return false;
        int md = monthDays(y, m);
        if (d < 1 || d > md) return false;
        return true;
    }
public:
    Date() : _year(1900), _month(1), _day(1) {}
    Date(int y, int m, int d) {
        if (valid(y,m,d)) { _year=y; _month=m; _day=d; }
        else { _year=1900; _month=1; _day=1; }
    }
    // prefix ++
    Date& operator++() {
        long ord = toOrdinal();
        ++ord;
        fromOrdinal(ord);
        return *this;
    }
    // postfix ++
    Date operator++(int) {
        Date tmp = *this;
        ++(*this);
        return tmp;
    }
    // prefix --
    Date& operator--() {
        long ord = toOrdinal();
        --ord;
        fromOrdinal(ord);
        return *this;
    }
    // postfix --
    Date operator--(int) {
        Date tmp = *this;
        --(*this);
        return tmp;
    }
    Date operator+(int days) const {
        Date res = *this;
        long ord = res.toOrdinal();
        ord += days;
        res.fromOrdinal(ord);
        return res;
    }
    Date operator-(int days) const {
        Date res = *this;
        long ord = res.toOrdinal();
        ord -= days;
        res.fromOrdinal(ord);
        return res;
    }
    // date - date => absolute days difference
    long operator-(const Date& other) const {
        long diff = toOrdinal() - other.toOrdinal();
        return diff >= 0 ? diff : -diff;
    }
    bool operator<(const Date& other) const {
        if (_year != other._year) return _year < other._year;
        if (_month != other._month) return _month < other._month;
        return _day < other._day;
    }
    friend ostream& operator<<(ostream& os, const Date& d) {
        os << d._year << '-' << d._month << '-' << d._day;
        return os;
    }
    // optional out() for compatibility
    void out() const {
        cout << _year << '-' << _month << '-' << _day << '\n';
    }
};

void Test() {
    int op;
    if(!(cin >> op)) return;
    int yy, mm, dd;
    if (op == 1 || op == 0) {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0) {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}

int main(){
    Test();
    return 0;
}
