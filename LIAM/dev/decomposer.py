
def pitchAxisToSweep(pitch):
    '''
        When both of the front wings swing backward,
        the shift in the aerodynamic center of the canards leads to a
        negative pitch moment relative to the center of mass.

        A positive pitch moment is generated when the  rear wings sweep forward
        Thus, by having the front wings sweep backward and
        the rear wings sweep forward, one can trim the flight state without
        an elevator 
    '''
    rsweepRange_min = 0
    rsweepRange_max = 90
    

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