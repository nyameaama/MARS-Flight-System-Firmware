
def pitchAxisToSweep(pitch_deg):
    '''
        When both of the front wings swing backward,
        the shift in the aerodynamic center of the canards leads to a
        negative pitch moment relative to the center of mass.

        A positive pitch moment is generated when the  rear wings sweep forward.

        Thus, by having the front wings sweep backward and
        the rear wings sweep forward, one can trim the flight state without
        an elevator 
    '''
    pos = []
    if pitch_deg >= 0:
        #Positive moment requested so front wings will move
        tp1 = calculateRL_pitch_pos(pitch_deg)
        tp2 = calculateRR_pitch_pos(pitch_deg)
        pos = [tp1, tp2]
        
    if pitch_deg < 0:
        tp1 = calculateFL_position_neg(pitch_deg)
        tp2 = calculateFR_position_neg(pitch_deg)
        pos = [tp1, tp2]

    return pos

def rollAxisToSweep(roll):
    '''
        Under the condition of asymmetric morphing (h2 = h4 = 0,
        h1 =-h3), the shift in the aerodynamic center of the front left
        wing and the rear left wing leads to a negative roll moment relative
        to the center of mass and an opposite roll moment under the
        condition of inverse morphing. 

        Linearly:
        
    '''
    c = 1



def calculateRL_pitch_pos(pitch):
    # Define the servo positions for 0 and 180 degrees pitch
    servo_pos_0_deg = 270
    servo_pos_180_deg = 360

    # Ensure that the pitch angle is within the valid range (-90 to 90 degrees)
    pitch_deg = max(0, min(90, pitch))

    # Calculate the servo position using linear interpolation
    servo_position = servo_pos_0_deg + ((servo_pos_180_deg - servo_pos_0_deg) / 180) * pitch_deg

    # Ensure that the servo position is within the allowed range (270 to 360)
    servo_position = max(270, min(360, servo_position))

    return servo_position


def calculateRR_pitch_pos(pitch_deg):
    # Define the servo positions for 0 and 180 degrees pitch
    servo_pos_0_deg = 90
    servo_pos_180_deg = 0

    # Ensure that the pitch angle is within the valid range (-90 to 90 degrees)
    pitch_deg = max(0, min(90, pitch_deg))

    # Calculate the servo position using linear interpolation
    servo_position = servo_pos_0_deg - ((servo_pos_0_deg - servo_pos_180_deg) / 180) * pitch_deg

    # Ensure that the servo position is within the allowed range (0 to 90)
    servo_position = max(0, min(90, servo_position))

    return servo_position

def calculateFL_position_neg(pitch_deg):
    # Define the servo positions for 0 and -90 degrees pitch
    servo_pos_0_deg = 270
    servo_pos_minus_90_deg = 180

    # Ensure that the pitch angle is within the valid range (0 to -90 degrees)
    pitch_deg = max(-90, min(0, pitch_deg))

    # Calculate the servo position using linear interpolation
    servo_position = servo_pos_0_deg + ((servo_pos_minus_90_deg - servo_pos_0_deg) / -90) * pitch_deg

    # Ensure that the servo position is within the allowed range (180 to 270)
    servo_position = max(180, min(270, servo_position))

    return servo_position


def calculateFR_position_neg(pitch_deg):
    # Define the servo positions for 0 and -90 degrees pitch
    servo_pos_0_deg = 90
    servo_pos_minus_90_deg = 180

    # Ensure that the pitch angle is within the valid range (0 to -90 degrees)
    pitch_deg = max(-90, min(0, pitch_deg))

    # Calculate the servo position using linear interpolation
    servo_position = servo_pos_0_deg + ((servo_pos_minus_90_deg - servo_pos_0_deg) / -90) * pitch_deg

    # Ensure that the servo position is within the allowed range (90 to 180)
    servo_position = max(90, min(180, servo_position))

    return servo_position

# Example usage:
#desired_pitch_deg = 50  # Replace with your desired pitch angle
#servo_position = calculate_servo_position(desired_pitch_deg)
#print(f"Servo Position for {desired_pitch_deg} Degrees Pitch:", servo_position)



print(pitchAxisToSweep(-58))