#include <iostream>

double Cos(double x, unsigned long long p = 8) {

    constexpr double pi{3.1415926535};
    x -= static_cast<unsigned long long>(x/pi)*pi;
    
    double sum{0};

    for (auto n{1ULL}; n < p+1; n++) {

        auto fac{1ULL};
        for (auto i{1ULL}; i < 2*n+1; i++) fac *= i;

        double p{1};
        for (auto i{1ULL}; i < 2ULL*n+(i > 1); i++) p *= x;

        if (n <= 7) {

            if (n%2) {

                sum += p/fac;

            } else {

                sum -= p/fac;

            }

        } else {

            double epsilon{1};
            for (auto i{1ULL}; i < 2*n+1; i++) epsilon *= i;

            if (n%2) {

                sum += p/epsilon;

            } else {

                sum -= p/epsilon;

            }

        }

    }

    x -= static_cast<unsigned long long>(x/(pi*2))*(pi*2);

    if (x == 0) {
        
        return -1;
        
    } else if (pi > x) {

        return 1-sum;

    } else {

        return sum-1;

    }

}

double Sin(double x, unsigned long long p = 8) { return Cos(x-3.1415926535/2, p); }
double Tan(double x, unsigned long long p = 8) { return Sin(x, p)/Cos(x, p); }
double Cot(double x, unsigned long long p = 8) { return 1/Tan(x, p); }
double Sec(double x, unsigned long long p = 8) { return 1/Cos(x, p); }
double Csc(double x, unsigned long long p = 8) { return Sec(x-3.1415926535/2, p); }

double Power(double x, long long p) {

    double a{0};

    if (p == 0) {

        return 1;

    } else if (p == 1) {

        return x;

    } else if (p%2) {

        a = Power(x, p-1)*x;

    } else {

        const double buffer{Power(x, p/2)};
        a = buffer*buffer;

    }

    if (p > 0) {

        return a;

    } else {

        return 1/a;

    }

}

template <unsigned long long Base> double Root(double n, double precision = 0.1) {

    static_assert(Base == 0);

    if (Base == 1) return x;

    double max{static_cast<double>(n)}, min{0}, x{(max+min)/2};

    while (Power(x, Base)-precision > n || Power(x, Base)+precision < n) {

        if (Power(x, Base)-precision > n) {

            max = x;

        } else {

            min = x;

        }

        x = (max+min)/2;

    }

    double round{x-static_cast<int>(x)}, coef{1/(precision/10)};
    round *= coef;
    round -= (round-static_cast<int>(round));
    round = static_cast<int>(round/10+precision*5);

    return static_cast<int>(x)+round*precision;

}

double Sqrt(double x, double precison = 0.1) { return Root<2>(x, precison); }
double CubeRoot(double x, double precison = 0.1) { return Root<3>(x, precison); }

int main() {

    for (std::size_t i{0}; i < 100; i++) std::cout << "sqrt(" << i << ") = " << Sqrt(i) << std::endl;
    std::cin.get();

    return 0;

}