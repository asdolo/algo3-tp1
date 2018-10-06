import os
import sys
import random
from subprocess import Popen, PIPE, STDOUT

# Aca se definen los tamanos de la entrada y la cantidad de muestras por cada n y V
MAX_N = 1000
MAX_V = 1000
CRECIMIENTO_N = 10
CRECIMIENTO_V = 10
CANT_MUESTRAS = 20

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
output_file_path = 'output/' + algoritmo + '.csv'

output_file = open(output_file_path, 'w')
output_file.write('n,V,resultado,tiempo (' + algoritmo + ')' + '\n')
output_file.close()

print('Ejecutando ' + apply_effects(algoritmo, color.BOLD) + ' con valores de entrada ' + apply_effects('0 <= n <= ' + str(MAX_N), [color.GREEN, color.BOLD]) + ' y ' + apply_effects('0 <= V <= ' + str(MAX_V), [color.GREEN, color.BOLD]) + '.')
print('Para cada valor de n y V se van a tomar ' + apply_effects(str(CANT_MUESTRAS), [color.GREEN, color.BOLD]) + ' muestras.')
print('El algoritmo se va a ejecutar un total de ' + apply_effects(str(CANT_MUESTRAS * (((MAX_N+CRECIMIENTO_N)/CRECIMIENTO_N) * (MAX_V+CRECIMIENTO_V)/CRECIMIENTO_V)), [color.GREEN, color.BOLD]) + ' veces.')

# Vario el tamano de n
for n in range(0, MAX_N+CRECIMIENTO_N, CRECIMIENTO_N):
    print('')
    print(' n=' + str(n) + '/' + str(MAX_N))
    # Vario el tamano de V
    for V in range(0, MAX_V+CRECIMIENTO_V, CRECIMIENTO_V):
        print('   V=' + str(V) + '/' + str(MAX_V))
        # Genero los inputs que van a ir al stdin por un pipe
        input = str(n) + ' ' + str(V) + '\n'

        # Genero cada numero del conjunto
        for i in range(0, n):
            input += str(random.randint(0, V)) + '\n'

        for i in range(0, CANT_MUESTRAS):
            p = Popen('./' + algoritmo, stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

print('Listo! Las mediciones fueron guardadas en ' + apply_effects(output_file_path, color.GREEN))
print('')
