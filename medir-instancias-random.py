import os
import sys
import random
from subprocess import Popen, PIPE, STDOUT

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

def clear_screen():
    print("\033[H\033[J")

def apply_effects(text, effects):
    res = ''
    for x in effects:
        res += x

    res += text

    for x in effects:
        res += color.END

    return res

def print_modo_de_uso():
    print(apply_effects('Modo de uso:', color.BOLD))
    print('  ' + 'python ' + os.path.basename(__file__) + ' [ALGORITMO]')
    print('')
    print(apply_effects('Algoritmos:', color.BOLD))
    print('  ' + apply_effects('fb, bf, fuerzabruta', color.RED))
    print('  ' + apply_effects('bt, backtracking', color.YELLOW))
    print('  ' + apply_effects('pd, dp, programaciondinamica', color.GREEN))
    print('')
    print(apply_effects('Ejemplo:', color.BOLD))
    print('  ' + 'python ' + os.path.basename(__file__) + ' fuerzabruta')
    print('')

# Main:
clear_screen()

if sys.version_info[0] != 2:
    print(apply_effects('Por favor, ejecute este script en Python 2.', [color.RED, color.BOLD]))
    print('')
    exit()

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
    print(apply_effects('Algoritmo \'' + parametro + '\' invalido.', color.BOLD))
    print('')
    print_modo_de_uso()
    exit()

try:
    p = Popen('./' + algoritmo, stdin=PIPE)
except OSError:
    print('No se encuentra el ejecutable del algoritmo ' + algoritmo + '.')
    print('Por favor, compile el algoritmo usando ' + apply_effects('make ' + algoritmo, color.BOLD) + ' o simplemente ' + apply_effects('make', color.BOLD) + ' para compilar todos los algoritmos.')
    print('')
    exit()

p.kill()

# Limpio los outputs viejos de este algoritmo
output_file_path = 'mediciones-' + algoritmo + '.csv'

output_file = open('output/' + output_file_path, 'w')
output_file.write('n,V,resultado,tiempo' + '\n')
output_file.close()





# Ejecutar algoritmo segun parametro
if algoritmo == 'fuerzabruta':
    # Vario el tamano de n
    for n in range(1, 20 + 1):
        print('')
        print(' n=' + str(n) + '/' + str(20))

        # Vario el tamano de V
        for V in range(0, 200 + 10, 10):
            print('   V=' + str(V) + '/' + str(200))
            # Genero los inputs que van a ir al stdin por un pipe
            input = str(n) + ' ' + str(V) + '\n'

            # Genero cada numero del conjunto
            for i in range(0, n):
                input += str(random.randint(0, V)) + '\n'

            for i in range(0, 20):
                p = Popen('./' + algoritmo + ' ' + output_file_path, stdin=PIPE, stdout=PIPE, shell=True)
                output = p.communicate(os.linesep.join([input]))[0]

elif algoritmo == 'backtracking':
    # Vario el tamano de n
    for n in range(0, 1000 + 10, 10):
        print('')
        print(' n=' + str(n) + '/' + str(1000))

        # Vario el tamano de V
        for V in range(0, 1000 + 10, 10):
            print('   V=' + str(V) + '/' + str(1000))
            # Genero los inputs que van a ir al stdin por un pipe
            input = str(n) + ' ' + str(V) + '\n'

            # Genero cada numero del conjunto
            for i in range(0, n):
                input += str(random.randint(0, int(3*V/n))) + '\n'

            for i in range(0, 20):
                p = Popen('./' + algoritmo + ' ' + output_file_path, stdin=PIPE, stdout=PIPE, shell=True)
                output = p.communicate(os.linesep.join([input]))[0]

elif algoritmo == 'programaciondinamica':
    # Vario el tamano de n
    for n in range(0, 1000 + 100, 100):
        print('')
        print(' n=' + str(n) + '/' + str(1000))

        # Vario el tamano de V
        for V in range(0, 1000 + 100, 100):
            print('   V=' + str(V) + '/' + str(1000))
            # Genero los inputs que van a ir al stdin por un pipe
            input = str(n) + ' ' + str(V) + '\n'

            # Genero cada numero del conjunto
            for i in range(0, n):
                input += str(random.randint(0, int(3*V/n))) + '\n'

            for i in range(0, 20):
                p = Popen('./' + algoritmo + ' ' + output_file_path, stdin=PIPE, stdout=PIPE, shell=True)
                output = p.communicate(os.linesep.join([input]))[0]

print('Listo! Las mediciones fueron guardadas en ' + apply_effects(output_file_path, color.GREEN))
print('')
