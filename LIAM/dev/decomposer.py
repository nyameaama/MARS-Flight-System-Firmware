
def pitchAxisToSweep(pitch_deg):
    '''
        When both of the front wings swing backward,
        the shift in the aerodynamic center of the canards leads to a
        negative pitch moment relative to the center of mass.

        A positive pitch moment is generated when the  rear wings sweep forward
        Thus, by having the front wings sweep backward and
        the rear wings sweep forward, one can trim the flight state without
        an elevator 
    '''
    # Define the maximum pitch angle (degrees) and the no pitch angle (degrees)
    max_pitch_deg = 270.0
    no_pitch_deg = 0.0
    
    # Calculate the pitch range (degrees) from no pitch to maximum pitch
    pitch_range = max_pitch_deg - no_pitch_deg
    
    # Calculate the ratio of pitch_deg within the pitch_range
    pitch_ratio = (pitch_deg - no_pitch_deg) / pitch_range
    
    # Calculate the corresponding angle for the Rear Left (RL) servo
    # The RL servo has a range of 0 - 270 degrees
    rl_servo_angle = 270.0 * pitch_ratio
    
    # Calculate the corresponding angle for the Rear Right (RR) servo
    # The RR servo has a range of 0 - 90 degrees
    rr_servo_angle = 90.0 * pitch_ratio
    
    # Return the servo angles for RL and RR
    return rl_servo_angle, rr_servo_angle
    

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

print(pitchAxisToSweep(130.5))