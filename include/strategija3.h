#ifndef STRATEGIJA3_H
#define STRATEGIJA3_H

#include "MyVector.h"
#include "studentas.h"
#include "LaikoMatavimas.h"

void spausdintiKietiakusIrVargsius(
    MyVector<Studentas>& vargsiai, 
    MyVector<Studentas>& kietiakai, 
    const string& vargsiuFailas, 
    const string& kietiakuFailas);

//3 strategija - Optimizuotas studentų skirstymas i vargsus ir kietiakus
void isskirtiVargsusIrKietiakusOpt(
    MyVector<Studentas>& grupe, 
    MyVector<Studentas>& vargsiai, 
    MyVector<Studentas>& kietiakai);

//testavimo funkcija su laiko matavimais
void testuotiSkaidymoStrategija3(const string& failoPavadinimas, const string& rezultataiAplankas);

#endif // STRATEGIJA3_H
