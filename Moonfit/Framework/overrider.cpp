#include "overrider.h"
#include <sstream>

overrider::overrider() : nbIndices(0) { nbIDsGiven = 0; }


overrider::overrider(TableCourse *kinetics, bool useSplines) : nbIndices(0) {
    nbIDsGiven = 0;
    if (!kinetics) {
        std::cerr << "ERR: Overrider created from an empty pointer to TableCourse" << std::endl;
        return;
    }
    for (int i = 0; i < kinetics->nbVar; ++i) {
        string extVarName = kinetics->headers[i + 1];
        this->learnSpl(extVarName, kinetics->getTimePoints(i), kinetics->getTimeCourse(i), useSplines);
    }
}


//std::map<key,int> name2ID;

int overrider::getID(key extNameVariable) {
    std::map<key, int>::iterator it = name2ID.find(extNameVariable);
    if (it != name2ID.end())
        return it->second;
    else {
        name2ID.insert(std::pair<key, int>(extNameVariable, nbIDsGiven));
        nbIDsGiven++;
        extend(nbIDsGiven + 1);
    }
    return (name2ID.find(extNameVariable))->second;
}

void overrider::reset() {
    nbIDsGiven = 0;
    name2ID.clear();
    nbIndices = 0;
    typeStorage.clear();
    dataFunct.clear();
    override.clear();
    for (int i = 0; i < (int) dataSpl.size(); ++i) {
        if (dataSpl[i]) delete dataSpl[i];
    }
}

void overrider::extend(int newNbIndices) {
    if (newNbIndices > nbIndices) {
        //std::cout << "Extend Overrider, new size " << newNbIndices << std::endl;
        typeStorage.resize(newNbIndices, NODATA);
        dataSpl.resize(newNbIndices, NULL);
        dataFunct.resize(newNbIndices);
        override.resize(newNbIndices, false);
        nbIndices = newNbIndices;
    }
}

bool overrider::hasData(key nameVar) {
    int index = getID(nameVar);
    if ((index < 0) || (index >= nbIndices)) return false;
    //std::cout << "HasData(index=" << index << "), max = " << nbIndices << std::endl;
    switch (typeStorage[index]) {
        case NODATA: {
            return false;
            break;
        }
        case SPLINE: {
            return (dataSpl[index] != NULL);
            break;
        }
        case FUNCTION: {
            return (dataFunct[index] != NULL);
            break;
        }
        default:
            return false;
    }
    return false; // this should not happen
}

double overrider::operator()(key nameVar, double value) {
    if (!hasData(nameVar)) return NAN;
    int index = getID(nameVar);
    switch (typeStorage[index]) {
        case SPLINE: {
            return (*(dataSpl[index]))(value);
            break;
        }
        case FUNCTION: {
            return (*(dataFunct[index]))(value);
            break;
        }
        default:
            return -1;
    }
    return -1;
}

bool overrider::operator()(key nameVar) {
    int index = getID(nameVar);
    if ((index < 0) || (index >= nbIndices)) return false;
    return override[index];
}

void overrider::learnSpl(key nameVar, vector<double> xs, vector<double> ys, bool yesSplnoLinearInterpol) {
    if (hasData(nameVar)) {
        std::cerr << "WRN : overrider::learnSpl, data was already saved for  " << nameVar << "; data overrided.\n";
    }
    int index = getID(nameVar);
    if (xs.size() != ys.size()) {
        std::cerr << "ERR: overrider::learnSpl, the vectors xs and ys should have the same size\n";
        return;
    }
    spline *SP = new spline();

    /*std::cout << "learning, ID=" << index << " " << CodingName(index) << std::endl;
    for(int i = 0; i < xs.size(); ++i){
        std::cout << xs[i] << "\t";
    } std::cout << std::endl;
    for(int i = 0; i < ys.size(); ++i){
        std::cout << ys[i] << "\t";
    } std::cout << std::endl;
    std::cout << std::endl;*/

    SP->set_points(xs, ys, yesSplnoLinearInterpol);
    extend(index + 1);    /// extend the data structure if required
    dataSpl[index] = SP;
    typeStorage[index] = SPLINE;
}

void overrider::setOver(key nameVar, bool value) { // put string("") to mean all
    if (nameVar.size() == 0) {                      //here, defaultkey might pose problem if key changes type
        for (std::map<key, int>::iterator it = name2ID.begin(); it != name2ID.end(); ++it) {
            if (hasData(it->first)) override[it->second] = value;
        }
        return;
    }
    int index = getID(nameVar);
    if ((index < 0) || (index >= nbIndices)) {
        if (!value) return;
        else {
            std::cerr << "ERR : overrider::setOver(index=" << index << ", value = " << (value ? "true" : "false")
                 << "), this index does not refer to any stored data (index out of bounds)\n";
            return;
        }
    }
    if ((!hasData(nameVar)) && (value)) {
        std::cerr << "ERR : overrider::setOver(" << nameVar << ", value = " << (value ? "true" : "false")
             << "), this index does not refer to any stored data (no data for this index)\n";
        return;
    }
    override[index] = value;
}


void overrider::learnFunct(key nameVar, double (*f)(double)) {
    if (hasData(nameVar)) {
        std::cerr << "WRN : overrider::learnFunct, data was already saved for " << nameVar << "; data overrided.\n";
    }
    int index = getID(nameVar);
    //extend(index+1); no more necessary because the getID will do it
    dataFunct[index] = f;
    typeStorage[index] = FUNCTION;
}

double ff(double x) {
    return x * (x - 1) + 3;
}

string overrider::print() {
    std::stringstream res;
    res << "Overrider with " << nbIndices << " curves\n";
    if (nbIndices != (int) typeStorage.size()) res << "ERR : typeStorage has size " << typeStorage.size() << std::endl;
    if (nbIndices != (int) override.size()) res << "ERR : typeStorage has size " << override.size() << std::endl;


    for (std::map<key, int>::iterator it = name2ID.begin(); it != name2ID.end(); ++it) {
        int i = it->second;
        res << it->first << ", Stored at position= " << it->second << "\t";
        switch (typeStorage[i]) {
            case NODATA: {
                res << "NODATA";
                break;
            }
            case SPLINE: {
                res << "SPLINE";
                break;
            }
            case FUNCTION: {
                res << "FUNCTION";
                break;
            }
            default: {
                res << "ERR: Non Identified type";
            }
        }
        res << "\t" << (override[i] ? "YES:override" : "NO:dont override") << std::endl;
    }

    return res.str();
}

void testOverrider() {
    // plan of test : variable 1, function, variable 2, no data, variable 3, spline, variable 4, linear interpol

    // for variable 1, will give ff
    // for variable 3
    vector<double> px;
    px.push_back(0.);
    px.push_back(3.0);
    px.push_back(6.0);
    px.push_back(9.0);
    px.push_back(12.0);
    px.push_back(18.0);
    px.push_back(24.0);

    vector<double> py;
    py.push_back(0.1);
    py.push_back(0.3);
    py.push_back(0.4);
    py.push_back(0.6);
    py.push_back(1.2);
    py.push_back(2.5);
    py.push_back(3.0);

    vector<string> Na = {"N0", "N1", "N2", "N3", "N4", "N5", "N6", "N7", "N8", "N9"};
    overrider ov = overrider();
    ov.learnFunct(Na[1], &(ff));
    ov.learnSpl(Na[3], px, py, true);
    ov.reset(); // just to see if resetting doesn't create segFaults ...
    ov.learnFunct(Na[1], &(ff));
    ov.learnSpl(Na[3], px, py, true);
    ov.learnSpl(Na[4], px, py, false);

    for (int i = 0; i < 10; ++i) {
        if (ov.hasData(Na[i])) std::cout << "Ov has data at index " << Na[i] << std::endl;
    }
    for (double dd = 0; dd < 30; dd += 0.5) {
        std::cout << "\n" << dd;
        for (int i = 1; i <= 4; ++i) {
            std::cout << "\t" << ov(Na[i], dd);
        }
    }

    return;

}
