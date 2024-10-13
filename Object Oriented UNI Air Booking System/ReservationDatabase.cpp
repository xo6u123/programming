// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "FlightSchedule.h" // FlightSchedule class definition

// ReservationDatabase default constructor loads flight reservations from the file Reservations.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores flight reservations into the file Reservations.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::cancelReservation( string id, int n )
{
    int num = 0;
    for (vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it) {
        if (id == it->getId()) {
            num++;
        }
        if (n == num) {
            reservations.erase(it);
            return;
        }

    }

} // end function cancelReservation

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::existReservation( string id )
{
    for (vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it) {
        if (it->getId() == id)
            return true;
    }
    return false;
}

void ReservationDatabase::display( string id )
{
    
    int num = 0;
    for (vector< Reservation >::iterator it = reservations.begin(); it != reservations.end(); ++it) {
        if (it->getId() == id) {
            num++;
            cout << endl;
            cout << num << " ";
            cout << "Ticket information:\n\n";
            cout << "Date: " << it->getDate() << endl;
            cout << "Flight: B7-" << it->getFlightNo() << endl << endl;
            FlightSchedule flights;
            int departureAirport = flights.getDepartureAirport(it->getFlightNo());
            int arrivalAirport = flights.getArrivalAirport(it->getFlightNo());

            cout << setw(9) << right << airportName[departureAirport] << " -> "
                << setw(9) << left << airportName[arrivalAirport] << endl;

            cout << setw(9) << right << flights.getDepartureTime(it->getFlightNo()) << "    ";
            cout << setw(9) << left << flights.getArrivalTime(it->getFlightNo()) << endl << endl;

            char ticketType[8][24] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                               "Senior Citizen Fare",     "Impaired Fare",
                                               "Impaired Companion Fare", "Military Fare" };

            int total = 0;
            int fare;
            for (int i = 1; i <= 7; i++)
                if (it->getTicket(i) > 0)
                {
                    fare = fullFare[departureAirport][arrivalAirport] * discount[i] / 100;
                    total += (fare * it->getTicket(i));
                    cout << right << setw(23) << ticketType[i] << "  TWD "
                        << setw(4) << fare << " x " << it->getTicket(i) << endl;
                }

            cout << "\nTotal: " << total << endl;
        }
            
    }
}

void ReservationDatabase::loadReservations()
{
    int numReservations;
    ifstream loadres("Reservations.dat", ios::in | ios::binary);
    char empty[12] = {};
    loadres.seekg(0, ios::end);
    numReservations = static_cast<int>(loadres.tellg()) / sizeof(Flight);
    loadres.seekg(0, ios::beg);
    Reservation temp;
    for (int i = 0; i < numReservations; i++) {
        loadres.read(reinterpret_cast<char*>(&temp),
            sizeof(Reservation));
        reservations.push_back(temp);
    }
    loadres.close();

}

void ReservationDatabase::storeReservations()
{

    ofstream save("Reservations.dat", ios::out | ios::binary);
    save.seekp(0, ios::end);
    save.write(reinterpret_cast<const char*>(&reservations),
        sizeof(Reservation));
    save.close();

}