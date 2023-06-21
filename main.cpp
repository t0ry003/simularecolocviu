//
// Created by rares on 6/11/2023.
//

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>

using namespace std;

class Car {
private:
    string mBrand;
    string mLicensePlate;
    uint16_t mYearOfFabrication;
    double mAverageConsumption;
    uint32_t mNumberOfKilometers;
public:
    Car(string _brand, string _license, uint16_t _year, double _consumption, uint32_t _numberofkm) : mBrand(_brand),
                                                                                                     mLicensePlate(
                                                                                                             _license),
                                                                                                     mYearOfFabrication(
                                                                                                             _year),
                                                                                                     mAverageConsumption(
                                                                                                             _consumption),
                                                                                                     mNumberOfKilometers(
                                                                                                             _numberofkm) {}

    string getBrand() const { return mBrand; }

    string getLicensePlate() const { return mLicensePlate; }

    uint16_t getYearOfFabrication() const { return mYearOfFabrication; }

    double getAverageConsumption() const { return mAverageConsumption; }

    uint32_t getNumberOfKilometers() const { return mNumberOfKilometers; }

    virtual double getFuelConsumption() const = 0;

    virtual double getFuelCost() const = 0;

    virtual string getType() const = 0;
};

class PetrolCar : public Car {
public:
    PetrolCar(string _brand, string _license, uint16_t _year, double _consumption, uint32_t _numberofkm) : Car(_brand,
                                                                                                               _license,
                                                                                                               _year,
                                                                                                               _consumption,
                                                                                                               _numberofkm) {}

    double getFuelConsumption() const override {
        return (0.879 * getNumberOfKilometers() * getAverageConsumption()) / 100;
    }

    double getFuelCost() const override {
        return getFuelConsumption() * 4.5;
    }

    string getType() const override {
        return "benzina";
    }
};

class DieselCar : public Car {
public:
    DieselCar(string _brand, string _license, uint16_t _year, double _consumption, uint32_t _numberofkm) : Car(_brand,
                                                                                                               _license,
                                                                                                               _year,
                                                                                                               _consumption,
                                                                                                               _numberofkm) {}

    double getFuelConsumption() const override {
        return (0.789 * getNumberOfKilometers() * getAverageConsumption()) / 100;
    }

    double getFuelCost() const override {
        return getFuelConsumption() * 4.8;
    }

    string getType() const override {
        return "diesel";
    }
};

class HybridCar : public Car {
public:
    HybridCar(string _brand, string _license, uint16_t _year, double _consumption, uint32_t _numberofkm) : Car(_brand,
                                                                                                               _license,
                                                                                                               _year,
                                                                                                               _consumption,
                                                                                                               _numberofkm) {}

    double getFuelConsumption() const override {
        return (getNumberOfKilometers() * getAverageConsumption() - 0.124 * getNumberOfKilometers()) / 100;
    }

    double getFuelCost() const override {
        return getFuelConsumption() * 4.5;
    }

    string getType() const override {
        return "hibrid";
    }
};

class ElectricCar : public Car {
public:
    ElectricCar(string _brand, string _license, uint16_t _year, double _consumption, uint32_t _numberofkm) : Car(_brand,
                                                                                                                 _license,
                                                                                                                 _year,
                                                                                                                 _consumption,
                                                                                                                 _numberofkm) {}

    double getFuelConsumption() const override {
        return 0;
    }

    double getFuelCost() const override {
        return 0;
    }

    string getType() const override {
        return "electrica";
    }
};

int main() {
    int n;
    cin >> n;
    vector<Car *> cars;

    for (int i = 1; i <= n; i++) {
        string brand, license, type;
        uint16_t year;
        double consumption;
        uint32_t numberofkm;
        cin >> brand >> type >> license >> year >> consumption >> numberofkm;
        if (type == "benzina") {
            cars.push_back(new PetrolCar(brand, license, year, consumption, numberofkm));
        } else if (type == "diesel") {
            cars.push_back(new DieselCar(brand, license, year, consumption, numberofkm));
        } else if (type == "hibrid") {
            cars.push_back(new HybridCar(brand, license, year, consumption, numberofkm));
        } else if (type == "electrica") {
            cars.push_back(new ElectricCar(brand, license, year, consumption, numberofkm));
        }
    }

    char c; // c -> cerinta
    cin >> c;
    if (c == 'a') {
        float sum;
        for (auto &car: cars) {
            sum += car->getFuelCost();
        }

        cout << fixed << setprecision(2) << sum << endl;
    } else if (c == 'b') {
        string brand, license, type;
        uint16_t year;
        double consumption;
        uint32_t numberofkm;

        while (cin >> brand >> type >> license >> year >> consumption >> numberofkm) {
            if (type == "benzina") {
                cars.push_back(new PetrolCar(brand, license, year, consumption, numberofkm));
            } else if (type == "diesel") {
                cars.push_back(new DieselCar(brand, license, year, consumption, numberofkm));
            } else if (type == "hibrid") {
                cars.push_back(new HybridCar(brand, license, year, consumption, numberofkm));
            } else if (type == "electrica") {
                cars.push_back(new ElectricCar(brand, license, year, consumption, numberofkm));
            }
        }

        uint32_t sumkm = 0;
        double consumptionavg = 0;
        for (auto &car: cars) {
            sumkm += car->getNumberOfKilometers();
            consumptionavg += car->getAverageConsumption();
        }

        cout << sumkm << " km" << endl;
        cout << fixed << setprecision(2) << consumptionavg / (double)cars.size() << " L/100km" << endl;
    }else if(c == 'c'){
        int nBen = 0, nDie = 0, nHib = 0, nEle = 0;
        for(auto &car: cars){
            if(car->getType() == "benzina"){
                nBen++;
            }else if(car->getType() == "diesel"){
                nDie++;
            }else if(car->getType() == "hibrid"){
                nHib++;
            }else if(car->getType() == "electrica"){
                nEle++;
            }
        }

        cout << "benzina -> " << nBen << endl;
        cout << "diesel -> " << nDie << endl;
        cout << "electrica -> " << nEle << endl;
        cout << "hibrid -> " << nHib << endl;
    } else if(c == 'd'){
        for(auto &car: cars){
            regex reg("[A-Z]{1,2}[0-9]{2,3}[A-Z]{3}");
            if(!regex_match(car->getLicensePlate(), reg)){
                cout << car->getLicensePlate() << ": numar de inmatriculare invalid" << endl;
            }
        }
    }

    return 0;
}
