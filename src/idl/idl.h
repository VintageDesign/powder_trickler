#pragma once

enum class dispense_status
{
    // No dispense in progress
    IDLE,
    IN_PROGRESS,
    // Dispense finished within the tolerance of the target value
    COMPLETE,
    // Failed to dispense within the tolerance of the target value 
    FAILURE,
};

// Send from the display to the micro when the user presses dispense. 
struct request_dispense
{
    double setpoint = 0.0;
    double tolerance = 0.0;
};


// Sent from the micro to display on change of the dispenser's status
struct dispense_status_update
{
    dispense_status status = IDLE;
};

// Sent from the micro to display on change of the scale's measurement
struct measurement_update
{
    double acutal_value = 0.0;
};



