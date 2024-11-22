import random

class Die_face:
    def __init__(self,value:int) -> None:
        self.value = value
        
class Die:
    def __init__(self,faces:list[Die_face]) -> None:
        self.faces = faces
        self.last_roll = 1
    def roll(self) -> int:
        roll = random.choice(self.faces)
        self.last_roll = roll
        return roll