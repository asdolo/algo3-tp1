import os
import sys
import random
from subprocess import Popen, PIPE

class color:
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    DARKCYAN = '\033[36m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'

def apply_effect(text, effect):
    return effect + text + color.END

def print_modo_de_uso():
    print apply_effect('Modo de uso:', color.BOLD)
    print '  ' + 'python tests.py [ALGORITMO]'
    print ''
    print apply_effect('Algoritmos:', color.BOLD)
    print '  ' + apply_effect('fb, bf, fuerzabruta', color.RED) + ' (default)'
    print '  ' + apply_effect('bt, backtracking', color.YELLOW)
    print '  ' + apply_effect('pd, dp, programaciondinamica', color.GREEN)
    print ''
    print apply_effect('Ejemplo:', color.BOLD)
    print '  ' + 'python tests.py fuerzabruta'
    print ''

# Main:
if len(sys.argv) != 2:
    print_modo_de_uso()
    exit()

parametro = sys.argv[1].lower()

if parametro in ['fb', 'bf', 'fuerzabruta']:
    algoritmo = 'fuerzabruta'
elif parametro in ['bt', 'bf', 'backtracking']:
    algoritmo = 'backtracking'
elif parametro in ['pd', 'dp', 'programaciondinamica']:
    algoritmo = 'programaciondinamica'
else:
    print apply_effect('Algoritmo \'' + parametro + '\' invalido.', color.BOLD)
    print ''
    print_modo_de_uso()
    exit()

try:
    p = Popen('./' + algoritmo, stdin=PIPE)
except OSError:
    print 'No se encuentra el ejecutable del algoritmo ' + algoritmo + '.'
    print 'Por favor, compile el algoritmo usando ' + apply_effect('make ' + algoritmo, color.BOLD) + ' o simplemente ' + apply_effect('make', color.BOLD) + ' para compilar todos los algoritmos.'
    print ''
    exit()

# Genero los inputs que van a ir al stdin por un pipe
n = 5
V = 15

input = str(n) + ' ' + str(V) + '\n'

for i in range (0, n):
    input += str(random.randint(0, 10)) + '\n'


p.communicate(os.linesep.join([input]))

