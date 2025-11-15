print() # Line spacer


name = input('Enter name: ').strip().title()
print(f'Hello {name}, Welcome to basic calculator! \n')

def user_input():
    a = float(input('Enter first value: '))
    b = float(input('Enter second value: '))
    return a , b


operation = input('Kindly choose an Operation from the options listed below by allocated number tag or simply word description : '
'\n\n 1) Addition or Add \n\n 2) Subtraction or Sub \n\n 3) Division or Div \n\n 4) Multiplication or Multp or Multiply ' 
'\n\n 5) Exponent or Pwr or Power \n\n 6) Floor division or Flr.div \n\n 7) Remainder or Remdr \n\n Your choice: ').lower()

# Debug to catch invalid user input
try:
    a , b = user_input()
except ValueError:
    print('Error: Invalid value input. Try again please.')


# Functions that will work on input values
def addition(a,b):
    ans1 = a + b
    return ans1
def subtraction(a,b):
    ans2 = a - b
    return ans2
def division(a,b):
    ans3 = a / b
    return ans3
def multiply(a,b):
    ans4 = a * b
    return ans4
def power(a,b):
    ans5 = a ** b
    return ans5
def floor_division(a,b):
    ans6 = a // b
    return ans6
def remainder(a,b):
    ans7 = a % b
    return ans7


# Acronyms used in order to simplify operation selection for user
if operation in ('add','addition','1)','1.','1'):
    print(addition(a,b))

elif operation in ('sub','subtract','2)','2.','2'):
    print(subtraction(a,b))

elif operation in ('pwr','power','expo','exponent','5)','5.','5'):
    print(power(a,b))

elif operation in ('multp','multiplication','multiply','4)','4.','4'):
    print(multiply(a,b))

elif operation in ('remdr','remainder','7)','7.','7'):
    print(remainder(a,b))

elif operation in ('flr.div','floor division','6)','6.','6'):
    print(floor_division(a,b))

elif operation in ('div','division','3)','3.','3'):
    print(division(a,b))

else:
    print('Input error. Try again.')

