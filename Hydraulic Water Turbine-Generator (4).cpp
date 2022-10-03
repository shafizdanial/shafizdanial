#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double pi = 3.14159265359;
float rho = 1000.0;
float g=9.81;
float corr_factor=1.05;

//function to input data for case 1
void input_data1(float V_dot[], float Pressure_drop[],float inlet_dia[],float outlet_dia[],float efficiency[], int& size){

    for (int i=0; i<size; i++){
        cout << "\nData Set " << i+1 << endl;
        cout <<"Inlet diameter (m): "; cin >> inlet_dia[i];
        cout <<"Outlet diameter (m): "; cin >> outlet_dia[i];
        cout <<"Volumetric flowrate (m^3/s): "; cin >> V_dot[i];
        cout <<"Pressure drop across turbine (Pa) : "; cin >> Pressure_drop[i];
        cout <<"Efficiency of Turbine-Generator (0-1): "; cin >>efficiency[i];
        cout <<endl;
    }
}

//function to input data for case 2
void input_data2(float V_dot[], float Work_generated[], float inlet_dia[], float outlet_dia[],float efficiency[], int& size){

    for (int i=0; i<size; i++){
        cout << "\nData Set " << i+1 << endl;
        cout <<"Inlet diameter (m): "; cin >> inlet_dia[i];
        cout <<"Outlet diameter (m): "; cin >> outlet_dia[i];
        cout <<"Volumetric flowrate (m^3/s): "; cin >> V_dot[i];
        cout <<"Work generated across generator (W) : "; cin >> Work_generated[i];
        cout <<"Efficiency of Turbine-Generator (0-1): "; cin >>efficiency[i];
        cout <<endl;
    }
}

//function to calculate velocity inlet
void calc_inlet_v(float v_inlet[], float inlet_dia[], float V_dot[],int& size){

    for (int i=0; i<size; i++){
        v_inlet[i] = V_dot[i]/((pi*pow(inlet_dia[i],2))/4);
    }
}

//function to calculate velocity outlet
void calc_outlet_v(float v_outlet[], float outlet_dia[], float V_dot[],int& size){

    for (int i=0; i<size; i++){
        v_outlet[i] = V_dot[i]/((pi*pow(outlet_dia[i],2))/4);
    }
}

//function to calculate pressure head
void calc_pressure_head(float Pressure_head[], float Pressure_drop[], int& size){

    for (int i=0; i<size; i++){
        Pressure_head[i]=Pressure_drop[i]/(rho*g);
    }
}

//function to calculate dynamic head
void calc_dynamic_head(float Dynamic_head[],float v_inlet[],float v_outlet[], int& size){

    for (int i=0; i<size; i++){
        Dynamic_head[i]=((v_inlet[i]*v_inlet[i])-(v_outlet[i]*v_outlet[i]))/(2*g);
    }
}

//function to calculate turbine head for case 1
void calc_h_turbine(float h_turbine[], float Pressure_head[], float Dynamic_head[], int& size){

    for (int i=0; i<size; i++){
        h_turbine[i]= Pressure_head[i]+Dynamic_head[i];
    }
}

//function to calculate turbine head for case 2
void calc_h_turbine2(float h_turbine[],float Work_generated[],float efficiency[],float V_dot[], int& size){
    for (int i=0; i<size; i++){
        h_turbine[i]=Work_generated[i]/(rho*V_dot[i]*g*efficiency[i]);
    }
}

//function to calculate work generated
void calc_power(float Work_generated[], float efficiency[], float V_dot[], float h_turbine[], int& size){

    for (int i=0; i<size; i++){
        Work_generated[i]=efficiency[i]*rho*V_dot[i]*g*h_turbine[i];
    }
}

//function to calculate pressure drop
void calc_pressure_drop(float Pressure_drop[], float h_turbine[], float v_inlet[], float v_outlet[], int& size){

    for (int i=0; i<size; i++){
        Pressure_drop[i]=rho*g*h_turbine[i]+(corr_factor*rho)*(((pow(v_outlet[i],2))/2)-((pow(v_inlet[i],2))/2));
    }
}

//function to display data case 1
void display_datacase1 (float inlet_dia[], float outlet_dia[], float V_dot[],float Pressure_drop[],float efficiency[],int& size){
    cout << "\n\nData for case 1:\n\n" << endl;
    cout << setw(25) << "D inlet (m)" << setw(25) << "D outlet (m)" << setw(25) << "V Flowrate (m^3/s)"
         << setw(25) << "Pressure Drop (Pa)" << setw(25) << "Turbine Efficiency" << endl;

    for(int i=0;i<size;i++){
    cout << setw(25) << inlet_dia[i] << setw(25) << outlet_dia[i]<< setw(25) << V_dot[i]
         << setw(25) << Pressure_drop[i] << setw(25) << efficiency[i] << endl;
    }
}

//function to display calculated data case 1
void display_calc_datacase1 (float v_inlet[],float v_outlet[], float Pressure_head[], float Dynamic_head[], float h_turbine[], float Work_generated[], int& size){
    cout << "\n\nCalculated Data for case 1:\n\n"<<endl;
    cout << setw(25) << "v Inlet (m/s)" << setw(25) << "v Outlet (m/s)" << setw(25) << "Pressure Head (m)"
         << setw(25) << "Dynamic Head (m)"<< setw(25) << "Turbine Head (m)" << setw(25) << "Work Generated (W)" <<endl;

    for (int i=0;i<size;i++){
    cout << setw(25) << v_inlet[i] << setw(25) << v_outlet[i] << setw(25) << Pressure_head[i]
         << setw(25) << Dynamic_head[i] << setw(25) << h_turbine[i] << setw(25) << Work_generated[i] << endl;
    }
}

//function to display data case 2
void display_datacase2 (float inlet_dia[],float outlet_dia[], float V_dot[], float Work_generated[],float efficiency[],int& size){
    cout << "\n\nData for case 2:\n\n" << endl;
    cout << setw(25) << "D inlet (m)" << setw(25) << "D outlet (m)" << setw(25) << "V Flowrate (m^3/s)"
         << setw(25) << "Work Generated (W)" << setw(25) << "Turbine Efficiency" <<endl;

    for(int i=0;i<size;i++){
        cout << setw(25) << inlet_dia[i] << setw(25) << outlet_dia[i]<< setw(25) << V_dot[i]
             << setw(25) << Work_generated[i] << setw(25) << efficiency[i] <<endl;
    }
}

//function to display calculated data case 2
void display_calc_datacase2 (float v_inlet[],float v_outlet[], float Pressure_head[],float Dynamic_head[],float h_turbine[],float Pressure_drop[],int& size){
    cout << "\n\nCalculated Data for case 2:\n\n"<<endl;
    cout << setw(25) << "v Inlet (m/s)" << setw(25) << "v Outlet (m/s)" << setw(25) << "Turbine Head (m)"
         << setw(25) << "Pressure Head (m)" << setw(25) << "Dynamic Head (m)" << setw(25) << "Pressure Drop (Pa)" << endl;

    for (int i=0;i<size;i++){
    cout << setw(25) << v_inlet[i] << setw(25) << v_outlet[i] << setw(25) << h_turbine[i]
         << setw(25) << Pressure_head[i] << setw(25) << Dynamic_head[i] << setw(25) << Pressure_drop[i] << endl;
    }
}

int main()
{

    int select,size;
    char choice;

    //if else (selection of case)
    cout<<"A turbine is attached to a generator. This program determines:\n";
    cout<<"1. The Work generated from the generator\n";
    cout<<"2. The Pressure Drop across the turbine\n\n";


    //Determine the array size
    cout<<"How many set of data that you want to input: ";
    cin>>size;

    while(true){

    //Select case
    cout<<"\nChoose the program you want to run"<<endl;
    cout<<"Case: ";
    cin>>select;

    if (select==1){

        //initialization of input variable
        float V_dot[size], Pressure_drop[size], inlet_dia[size], outlet_dia[size], efficiency[size];
        //initialization of output variable
        float v_inlet[size], v_outlet[size], h_turbine[size], Work_generated[size], Pressure_head[size], Dynamic_head[size];

        input_data1(V_dot, Pressure_drop, inlet_dia, outlet_dia, efficiency, size);

        //call function
        calc_inlet_v(v_inlet, inlet_dia, V_dot, size);
        calc_outlet_v(v_outlet, outlet_dia, V_dot, size);
        calc_pressure_head(Pressure_head, Pressure_drop, size);
        calc_dynamic_head(Dynamic_head, v_inlet, v_outlet, size);
        calc_h_turbine(h_turbine, Pressure_head, Dynamic_head, size);
        calc_power(Work_generated, efficiency, V_dot, h_turbine, size);

        display_datacase1 (inlet_dia, outlet_dia, V_dot, Pressure_drop,efficiency, size);
        display_calc_datacase1 (v_inlet,v_outlet, Pressure_head, Dynamic_head, h_turbine, Work_generated, size);

        cout << "\n\nDo you wish to continue the program? (y = to continue, n = to terminate): ";
        cin >> choice;
        if(choice=='y'){
            continue;
        }
        else{
            break;
        }
    }//end if select

    else if (select==2){
        //initialization of input variable
        float V_dot[size],Work_generated[size], inlet_dia[size], outlet_dia[size], efficiency[size];
        //initialization of output variable
        float v_inlet[size], v_outlet[size], h_turbine[size], Pressure_drop[size], Pressure_head[size], Dynamic_head[size];

        //input data for case 2
        input_data2(V_dot, Work_generated, inlet_dia, outlet_dia, efficiency, size);

        //call function
        calc_inlet_v(v_inlet, inlet_dia, V_dot, size);
        calc_outlet_v(v_outlet, outlet_dia, V_dot, size);
        calc_h_turbine2(h_turbine, Work_generated, efficiency, V_dot, size);
        calc_pressure_drop (Pressure_drop, h_turbine, v_inlet, v_outlet, size);
        calc_pressure_head(Pressure_head, Pressure_drop, size);
        calc_dynamic_head(Dynamic_head, v_inlet, v_outlet, size);



        //display data
        display_datacase2 (inlet_dia, outlet_dia, V_dot, Work_generated,efficiency, size);
        display_calc_datacase2(v_inlet,v_outlet, Pressure_head, Dynamic_head, h_turbine, Pressure_drop, size);

        cout<<"\n\nDo you wish to continue the program? (y = to continue, n = to terminate): ";
        cin>>choice;
        if (choice=='y'){
            continue;
        }
        else{
            break;
        }
    }

    else{
        cout<<"\nInvalid case! Please enter 1 or 2." << endl;
    }

}//end while
    return 0;
}


