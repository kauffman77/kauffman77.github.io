#!/usr/bin/python3
import time

msg = r"""#======================================================================================#
#       0_                                                                             #
#        \`.     ___           __  __                           ___               _ __ #
#         \ \   / __>0        / / / /___ _____  ____  __  __   /   |  ____  _____(_) / #
#     /\  /  |/' /           / /_/ / __ `/ __ \/ __ \/ / / /  / /| | / __ \/ ___/ / /  #
#    /  \/   `  ,`'--.      / __  / /_/ / /_/ / /_/ / /_/ /  / ___ |/ /_/ / /  / / /   #
#   / /(___________)_ \    /_/ /_/\__,_/ .___/ .___/\__, /  /_/  |_/ .___/_/  /_/_/    #
#   |/ //.-.   .-.\\ \ \              /_/   /_/    /____/         /_/                  #
#   0 // :@ ___ @: \\ \/                                                               #
#     ( o ^(___)^ o ) 0                                                                #
#      \ \_______/ /          ______            ___          ____              ______  #
#  /\   '._______.'--.       / ____/___  ____  / ( )_____   / __ \____ ___  __/ / / /  #
#  \ /|  |<_____>    |      / /_  / __ \/ __ \/ /|// ___/  / / / / __ `/ / / / / / /   #
#   \ \__|<_____>____/|__  / __/ / /_/ / /_/ / /  (__  )  / /_/ / /_/ / /_/ /_/_/_/    #
#    \____<_____>_______/ /_/    \____/\____/_/  /____/  /_____/\__,_/\__, (_|_|_)     #
#        |<_____>    |                                               /____/            #
#        :<_____>____:                                                                 #
#       / <_____>   /|              Did you really think we're that cruel?             #
#  jgs /  <_____>  / |                      Prof K. and the 216 Staff                  #
#     /___________/  |                                                                 #
#======================================================================================#

"""

def put_cursor(row,col):
  """Puts the cursor at the given row/col in the terminal"""
  print(f"\033[{row};{col}H",end="")

def hide_cursor():
  """Hide the terminal cursor """
  print(f"\033[?25l",end="")

def show_cursor():
  """Show the terminal cursor"""
  print(f"\033[?25h",end="")

def printstr_pos(string,startrow):
  '''Uses terminal cursor positioning to print a message.

  Without position, programs like vi / nano / less screw up the
  printing of newline-based messages; this funciton prevents that

  '''
  lines = string.splitlines()
  for (i,line) in enumerate(lines):
    put_cursor(startrow+i,0)
    print(line,end="",flush=True)
  put_cursor(startrow+len(lines),0)

def scrolldown_topbanner(msg,delay_sec):
  """Scroll down a multiline banner message from the top of the screen"""
  hide_cursor()
  lines = msg.splitlines()
  for i in range(len(lines)):
    endlines = lines[-(i+1):]
    for (r,line) in enumerate(endlines):
      printstr_pos(line,r+1)
    time.sleep(delay_sec)
  show_cursor()

# run when executed
scrolldown_topbanner(msg,0.1)
