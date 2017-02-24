
'''
Question 1.
Write a program in Python that when executed will
prompt the user for text input and reply with the correct response as provided
in the following table. The program should continue to prompt for input and
reply with the appropriate response until an input value is provided that is not
valid, i.e. not in the table. Please make all input case insensitive.

Input   Output

Red     Green
Green   Black
Black   Blue
Blue    Yellow
Yellow  Red
White   Black
Purple  Green

'''

# Design Notes

# Python Doc.: https://docs.python.org/2/library/index.html
# Style Convention: https://www.python.org/dev/peps/pep-0008/
# Python do's and don'ts: https://docs.python.org/2/howto/doanddont.html

# Do we need to strip leading and trailing whitespace?
# We can use a bool. to enable and disable this in case they don't want us to do that.

# At first I'm thinking we need an to represent each color as an int. and store
# the mapping in an array of int.s. But python doesn't have enums like C does.
# Python has allot of built in features, we don't need enums on second thought.

# This table reminds me of a dictionary ADT.

# Dictionaries are easy in python, I'll use that to store the IO map. Like so:

'''
# Since they want this to be case in sensitive I'll make the keys to this map
# all lower case. This way I can query the map by lower casing the input string.
# Refresh on python maps: https://docs.python.org/2/library/stdtypes.html#mapping-types-dict
IO_COLOR_MAP = {
'Red':'Green',
'Green':'Black',
'Black':'Blue',
'Blue':'Yellow',
'Yellow':'Red',
'White':'Black',
'Purple':'Green'
}
'''


# Testing
'''
# Its easy to test all IO here

Darbin-Reyess-MacBook-Pro:Intel darbinreyes$ python Q_1_colors.py
red
Green
blue
Yellow
black
Blue
white
Black
haha
Bye!

# Test if trimming works
Darbin-Reyess-MacBook-Pro:Intel darbinreyes$ python Q_1_colors.py
    red
Green
          black
Blue
yo
Bye!

# Tested gracefully terminates on control+d and control+c.

'''

# This table never changes, lets make it const to prevent accidental changes to it.
# http://stackoverflow.com/questions/17291791/why-no-const-in-python

# Don't forget to handle errors gracefully.

# Provide the source with minimal comments in case they don't want all this verbose commenting.

# Return output color for inputcolor
# pre-condition, inputcolor must be stripped of leading and trailing whitespace,
# and must be all lower cased.
# Returns the output color as a string, or None if input was not a key in the map.
def get_output_color(input_color=''):
    # define our map.
    IO_COLOR_MAP = {
      'red':'Green',
      'green':'Black',
      'black':'Blue',
      'blue':'Yellow',
      'yellow':'Red',
      'white':'Black',
      'purple':'Green'
      }

    # get the output color and return it if valid, else return None
    if input_color in IO_COLOR_MAP:
        return IO_COLOR_MAP[input_color]

    return None

# returns the user's input color after cleanup.
# returns the input string or None if an error occured.
def get_input_color(trim_input=True,prompt_user=True): # Make it easy to disable trimming and prompting in case they don't want that.

    input_prompt_str = ''

    if prompt_user:
        input_prompt_str =  'input:  '

    # note: use control+d to input EOF
    # read input from user
    try:
        s = raw_input(input_prompt_str)

        if trim_input:
            s = s.strip()
            s = s.lower()

        return s

    except: # catch EOFError and KeyboardInterrupt.
        return None

def main():
    '''

    The program should continue to prompt for input and
    reply with the appropriate response until an input value is provided that is not
    valid, i.e. not in the table.

    '''
    while True:
      input_color = get_input_color(trim_input=True,prompt_user=False)

      if input_color == None:
          return 1

      output_color = get_output_color(input_color)

      if output_color == None:
        print 'Bye!'
        return 0

      print output_color

    return 1

# Define our main function.
if __name__=='__main__':
  main()
