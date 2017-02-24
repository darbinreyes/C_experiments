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

# Returns the user's input color after cleanup.
# Returns the input string or None if an error occured.
def get_input_color(trim_input=True,prompt_user=True): # Make it easy to disable trimming and prompting in case they don't want that.

    input_prompt_str = ''

    if prompt_user:
        input_prompt_str =  'input:  '

    # note: use control+d/c to input EOF
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

    The program should continue to prompt for input and reply with the
    appropriate response until an input value is provided that is not valid,
    i.e. not in the table.

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
