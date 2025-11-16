print() # Line spacer




# Debug to catch invalid user input
try:
    
    name = input('Enter name: ').strip().title()
    print(f'Hello {name}, Welcome to basic calculator! \n')

    def user_input():
        a = float(input('Enter first value: '))
        b = float(input('Enter second value: '))
        return a , b
    
    operation = input('Kindly choose an Operation from the options listed below by allocated number tag or simply word description : '
    '\n\n 1) Addition or Add \n\n 2) Subtraction or Sub \n\n 3) Division or Div \n\n 4) Multiplication or Multp or Multiply ' 
    '\n\n 5) Exponent or Pwr or Power \n\n 6) Floor division or Flr.div \n\n 7) Remainder or Remdr \n\n Your choice: ').lower()

    a , b = user_input()

# Functions that will work on input values
    def operations(a,b):
        if operation in ('add','addition','1)','1.','1'):
            return a + b
        elif operation in ('sub','subtract','2)','2.','2'):
            return a - b

        elif operation in ('pwr','power','expo','exponent','5)','5.','5'):
            return a ** b

        elif operation in ('multp','multiplication','multiply','4)','4.','4'):
            return a * b

        elif operation in ('remdr','remainder','7)','7.','7'):
            return a % b

        elif operation in ('flr.div','floor division','6)','6.','6'):
            return a // b

        elif operation in ('div','division','3)','3.','3'):
            return a / b

        else:
           print('Invalid operation input. Try again.')

    print(operations(a,b))

except ValueError:
    print('Error: Value or operation input error.')
