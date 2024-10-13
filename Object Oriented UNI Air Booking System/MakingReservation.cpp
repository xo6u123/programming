// MakingReservation.cpp
// Member-function definitions for class MakingReservation.
#include <iostream>
#include <iomanip>
#include "MakingReservation.h" // MakingReservation class definition

// MakingReservation constructor initializes data members
MakingReservation::MakingReservation( ReservationDatabase &theReservationDatabase,
                                      FlightSchedule &theFlightSchedule )
   : reservationDatabase( theReservationDatabase ),
     flightSchedule( theFlightSchedule )
{
} // end MakingReservation constructor

void MakingReservation::execute()
{
   // choose departure airport by input its code,
   // and assign the code to departureAirport
   int departureAirport;
   do
   {
      cout << "\nDeparture airport:\n";
      for( int i = 1; i <= 11; i++ )
         cout << setw( 2 ) << i << ". " << airportName[ i ] << endl;
      cout << "? ";

      cin >> departureAirport;
   } while( departureAirport < 1 || departureAirport > 11 );

   int arrivalAirport;
   // choose arrival airport by input its code, and assign the code to arrivalAirport
   chooseArrivalAirport( departureAirport, arrivalAirport );

   Reservation newReservation;

   string date;
   cout << "\nDeparture Date (yyyy/mm/dd)¡G ";
   cin >> date;
   newReservation.setDate( date );
   cout << endl;

   flightSchedule.display( departureAirport, arrivalAirport, date );

   string flightNo;
   do
   {
      cout << "\nFlight Number: ";
      cin >> flightNo;
   } while( !flightSchedule.exist( flightNo, departureAirport, arrivalAirport ) );
   newReservation.setFlightNo( flightNo );

   int tickets[ 8 ];
   inputNumTickets( tickets );
   newReservation.setTickets( tickets );

   displayReservation( newReservation );

   string id;
   cout << "\nID Number: ";
   cin >> id;
   newReservation.setId( id );

   string name;
   cout << "\nName: ";
   cin >> name;
   newReservation.setName( name );

   string mobile;
   cout << "\nMobile: ";
   cin >> mobile;
   newReservation.setMobile( mobile );

   reservationDatabase.addReservation( newReservation );

   cout << "\nBooking Completed!\n";
}

// choose arrival airport by input its code, and assign the code to arrivalAirport
void MakingReservation::chooseArrivalAirport( int departureAirport, int &arrivalAirport )
{

    do {
        cout << "\nArrival airport:\n";
        for (int i = 1; i <= 11; i++)
            if (fullFare[departureAirport][i] != 0) {
                cout << setw(2) << i << ". " << airportName[i] << endl;
            }
        cout << "? ";

        cin >> arrivalAirport;
    } while (fullFare[departureAirport][arrivalAirport] == 0);

}

// input the number of tickets for each ticket type, and assign them to tickets
void MakingReservation::inputNumTickets( int tickets[] )
{
   do
   {
      cout << "\nNumber of infant tickets (0 ~ 4): ";
      cin >> tickets[ 3 ];
   } while( tickets[ 3 ] < 0 || tickets[ 3 ] > 4 );

   int numTickets = 0;
   int numAdults = 0;
   do
   {
      numTickets = 0;

      cout << "\nNumber of full fare tickets (0 ~ 4): ";
      cin >> tickets[ 1 ];
      numTickets += tickets[ 1 ];

      cout << "\nNumber of child tickets (0 ~ 4): ";
      cin >> tickets[ 2 ];
      numTickets += tickets[ 2 ];

      cout << "\nNumber of senior citizen tickets (0 ~ 4): ";
      cin >> tickets[ 4 ];
      numTickets += tickets[ 4 ];

      cout << "\nNumber of impaired tickets (0 ~ 4): ";
      cin >> tickets[ 5 ];
      numTickets += tickets[ 5 ];

      cout << "\nNumber of impaired companion tickets (0 ~ 4): ";
      cin >> tickets[ 6 ];
      numTickets += tickets[ 6 ];

      cout << "\nNumber of military tickets (0 ~ 4): ";
      cin >> tickets[ 7 ];
      numTickets += tickets[ 7 ];

      numAdults = tickets[ 1 ] + tickets[ 4 ] + tickets[ 5 ] + tickets[ 6 ] + tickets[ 7 ];

      if( numTickets > 4 )
         cout << "\nThis booking system accepts a maximum of 4 passengers"
              << "( including children ) per booking.\n"
              << "If there are more than 4 passengers, please make multiple bookings.\n";
      else if( numAdults < tickets[ 3 ] )
         cout << "\nEach infant must always be accompanied by at least one adult.\n";

   } while( numTickets > 4 || numAdults < tickets[ 3 ] );

   cout << endl;
}

void MakingReservation::displayReservation( Reservation reservation )
{
;   
    cout << "Ticket information:\n\n";
    cout << "Date: " << reservation.getDate() << endl;
    cout << "Flight: B7-" << reservation.getFlightNo() << endl << endl;

    int departureAirport = flightSchedule.getDepartureAirport(reservation.getFlightNo());
    int arrivalAirport = flightSchedule.getArrivalAirport(reservation.getFlightNo());

    cout << setw(9) << right << airportName[departureAirport] << " -> "
        << setw(9) << left << airportName[arrivalAirport] << endl;

    cout << setw(9) << right << flightSchedule.getDepartureTime(reservation.getFlightNo()) << "    ";
    cout << setw(9) << left << flightSchedule.getArrivalTime(reservation.getFlightNo()) << endl << endl;

    char ticketType[8][24] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                       "Senior Citizen Fare",     "Impaired Fare",
                                       "Impaired Companion Fare", "Military Fare" };

    int total = 0;
    int fare;
    for (int i = 1; i <= 7; i++)
        if (reservation.getTicket(i) > 0)
        {
            fare = fullFare[departureAirport][arrivalAirport] * discount[i] / 100;
            total += (fare * reservation.getTicket(i));
            cout << right << setw(23) << ticketType[i] << "  TWD "
                << setw(4) << fare << " x " << reservation.getTicket(i) << endl;
        }

    cout << "\nTotal: " << total << endl;

}