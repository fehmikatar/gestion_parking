#ifndef PARKING_RESERVATION_H
#define PARKING_RESERVATION_H

#define MAX_PARKING_RESERVATIONS 100
#define MAX_PARKING_LOCATIONS 50

// Rename the structures to be more specific
typedef struct {
    int reservation_id;
    char vehicle_brand[20];
    char vehicle_model[20];
    char license_plate[10];
    int reservation_days;
    int arrival_hour;
    int departure_hour;
} ParkingReservation;

typedef struct {
    int parking_id;
    char parking_location[50];
    int parking_capacity;
} ParkingLocation;

// Rename functions to avoid conflicts
int load_parking_reservations(ParkingReservation reservations[], const char* filename);
void create_parking_reservation(const char* filename);
void display_parking_reservations_by_filename(const char* filename);
void display_parking_reservations_by_date(const char *date, int parking_id);
void delete_parking_reservation(const char* filename, int reservation_id);
void save_parking_reservations(ParkingReservation reservations[], int reservation_count, const char* filename);

// Parking-related functions
int load_parking_locations(ParkingLocation parking_locations[], const char* filename);
void save_parking_locations(ParkingLocation parking_locations[], int location_count, const char* filename);
void list_available_parking_locations(ParkingLocation parking_locations[], int location_count);

#endif