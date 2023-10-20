
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
        #Positive moment requested so rear wings will move
        tp1 = decomposeRL("Pitch", pitch_deg)
        tp2 = decomposeRR("Pitch", pitch_deg)
        pos = [tp1, tp2]
        
    if pitch_deg < 0:
        #Negative moment requested so rear wings will move
        #Multiply by negative -1 to get the positive value
        tp1 = decomposeFL("Pitch", (pitch_deg * -1))
        tp2 = decomposeFR("Pitch", (pitch_deg * -1))
        pos = [tp1, tp2]

    return pos

def rollAxisToSweep(roll_deg):
    '''
        Under the condition of asymmetric morphing (h2 = h4 = 0,
        h1 =-h3), the shift in the aerodynamic center of the front left
        wing and the rear left wing leads to a negative roll moment relative
        to the center of mass and an opposite roll moment under the
        condition of inverse morphing. 

        Linearly:
        
    '''
    pos = []
    if roll_deg >= 0:
        #Positive moment requested so right side wings will move
        tp1 = decomposeFR("Roll", roll_deg)
        tp2 = decomposeRR("Roll", roll_deg)
        pos = [tp1, tp2]
        
    if roll_deg < 0:
        #Negative moment requested so left side wings will move
        #Multiply by negative -1 to get the positive value
        tp1 = decomposeFL("Roll", (roll_deg * -1))
        tp2 = decomposeRL("Roll", (roll_deg * -1))
        pos = [tp1, tp2]

    return pos


def decomposeFL(angleType, angleValue):
    finalPos = 0
    if(angleType == "Pitch"):
        # Angle type is pitch:
        # Pitch -> 0 - 90
        # ServoPos (FL) -> 180 - 270
        finalPos = maptoRange(angleValue, 0, 90, 270, 180)

    if(angleType == "Roll"):
        # Angle type is Roll:
        # Roll -> 0 - 180
        # ServoPos (FL) -> 180 - 270
        finalPos = maptoRange(angleValue, 0, 180, 270, 180)

    return finalPos

def decomposeFR(angleType, angleValue):
    finalPos = 0
    if(angleType == "Pitch"):
        # Angle type is pitch:
        # Pitch -> 0 - 90
        # ServoPos (FR) -> 90 - 180
        finalPos = maptoRange(angleValue, 0, 90, 90, 180)

    if(angleType == "Roll"):
        # Angle type is Roll:
        # Roll -> 0 - 180
        # ServoPos (FR) -> 90 - 180
        finalPos = maptoRange(angleValue, 0, 180, 90, 180)

    return finalPos

def decomposeRL(angleType, angleValue):
    finalPos = 0
    if(angleType == "Pitch"):
        # Angle type is pitch:
        # Pitch -> 0 - 90
        # ServoPos (RL) -> 180 - 270
        finalPos = maptoRange(angleValue, 0, 90, 270, 180)

    if(angleType == "Roll"):
        # Angle type is Roll:
        # Roll -> 0 - 180
        # ServoPos (RL) -> 180 - 270
        finalPos = maptoRange(angleValue, 0, 180, 270, 180)

    return finalPos

def decomposeRR(angleType, angleValue):
    finalPos = 0
    if(angleType == "Pitch"):
        # Angle type is pitch:
        # Pitch -> 0 - 90
        # ServoPos (RR) -> 90 - 180
        finalPos = maptoRange(angleValue, 0, 90, 90, 180)

    if(angleType == "Roll"):
        # Angle type is Roll:
        # Roll -> 0 - 180
        # ServoPos (RR) -> 90 - 180
        finalPos = maptoRange(angleValue, 0, 180, 90, 180)

    return finalPos

def maptoRange(input, input_start, input_end, output_start, output_end):
    #Map input range to output range
    slope = (output_end - output_start) / (input_end - input_start)
    output = output_start + slope * (input - input_start)
    return output

# Example usage:
#desired_pitch_deg = 50  # Replace with your desired pitch angle
#servo_position = calculate_servo_position(desired_pitch_deg)
#print(f"Servo Position for {desired_pitch_deg} Degrees Pitch:", servo_position)



print(pitchAxisToSweep(-58))