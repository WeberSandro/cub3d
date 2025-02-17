# cub3d
Repositorio destinado ao curso 42 luxembourg


## Make File
Melhorias no Makefile:
Suporte ao Valgrind:

Adicionei uma regra chamada valgrind para rodar o executável com Valgrind, verificando vazamentos de memória.
Separação de Objetos em Diretórios:

Arquivos objeto são compilados no diretório obj/, organizado por subdiretórios.
Mensagens Coloridas:

Adicionei mensagens coloridas para tornar a saída mais legível.
Melhor Modularidade:

Uso do wildcard para capturar todos os arquivos .c recursivamente no diretório src.
Flags de Debugging:

Adicionei a flag -g ao CFLAGS para facilitar a depuração com ferramentas como o GDB.
Memcheck:

Adicionei a regra memcheck para recompilar o projeto e rodar o Valgrind.
Criar Diretórios Automaticamente:

O diretório obj/ é criado dinamicamente para armazenar os objetos.
Inclusão de Cabeçalhos:

Usei a flag -I para garantir que o compilador encontre os arquivos no diretório include.


## Como Usar
Compilar o projeto:

bash
Copiar código
make
Limpar arquivos objeto:

bash
Copiar código
make clean
Limpar tudo (objetos e binários):

bash
Copiar código
make fclean
Recompilar tudo:

bash
Copiar código
make re
Testar com Valgrind:

bash
Copiar código
make valgrind
Recompilar e testar memória:

bash
Copiar código
make memcheck

## 1. Entenda o Projeto

Os parâmetros do mapa (ex.: paredes 1, espaços vazios 0, pontos de spawn do jogador N, S, E, W).
O funcionamento do raycasting para renderizar paredes em 3D.
As bibliotecas permitidas, especialmente a MiniLibX.
2. Planejamento
Divida o projeto em partes:
Leitura e validação do mapa
Carregar o arquivo .cub.
Verificar erros no formato do mapa (ex.: paredes fechadas, caracteres inválidos).
Renderização do mapa 2D
Renderizar um minimapa simples.
Movimentação do jogador
Implementar os controles básicos (andar para frente/trás, virar a câmera).
Raycasting para renderização 3D
Implementar o cálculo de interseções de raios com paredes.
Renderizar as "paredes" baseadas na distância.
Adições e ajustes
Implementar texturas nas paredes, portas, sprites (se necessário).
Melhorar performance e corrigir bugs.
3. Por Onde Começar
(1) Leitura e validação do mapa
Função: parse_map()

Leia o arquivo .cub.
Valide o formato do mapa (ex.: bordas fechadas, símbolos válidos, ponto de spawn único).
Estude:

Como manipular arquivos em C (open, read, close).
Estruturas de dados para armazenar o mapa (ex.: matrizes de caracteres).
Algoritmos de validação de mapas (ex.: flood-fill para verificar paredes fechadas).
(2) Renderização do minimapa
Função: render_minimap()

Renderize um grid 2D simples para representar o mapa.
Use funções básicas da MiniLibX (mlx_pixel_put ou mlx_image).
Estude:

Como desenhar na tela com a MiniLibX.
Representação de mapas em 2D.
(3) Movimentação do jogador
Função: move_player()

Atualize a posição do jogador com base na entrada do teclado.
Verifique colisões com paredes no minimapa.
Estude:

Detecção de teclas na MiniLibX.
Estruturas de controle (ex.: structs para posição do jogador).
(4) Raycasting básico
Função: raycast()

Calcule as interseções de raios lançados do ponto de vista do jogador.
Renderize linhas verticais para simular "paredes".
Estude:

Matemática de vetores (senos, cossenos, tangentes).
Como projetar uma cena 3D a partir de um mapa 2D.
4. Cronograma Sugerido
Semana 1: Base do Projeto
Leia o mapa e implemente validações básicas.
Renderize o mapa em 2D como minimapa.
Garanta que o jogador possa se movimentar no minimapa.
Semana 2: Renderização 3D
Implemente o raycasting básico.
Renderize paredes sem texturas.
Semana 3: Adições e Melhorias
Adicione texturas.
Ajuste a movimentação do jogador.
Teste e corrija bugs.
5. Ferramentas e Recursos
Debugging: Use gdb ou printf para identificar problemas.
Referências Matemáticas: Relembre funções trigonométricas para cálculos de ângulos.
MiniLibX: Estude bem a documentação e os exemplos básicos.

## Pontos Cobertos no Código
- Movimentação do Jogador:

- Teclas W, A, S, D para mover o jogador (implementado em player.c).
Rotação da câmera com as setas esquerda e direita (implementado parcialmente em player.c).
Renderização 3D:

- Algoritmo de raycasting básico implementado em render.c.
Uso da MiniLibX para desenhar pixels na tela.
Organização Modular:

- Código dividido em arquivos separados (map.c, player.c, render.c, utils.c, etc.).
Uso de cabeçalhos para organizar as declarações.
Makefile:

- Contém todas as regras obrigatórias (all, clean, fclean, re).
Usa os flags exigidos (-Wall -Wextra -Werror).
Mapa Básico:

- Um mapa básico é carregado em get_map (dentro de map.c).
O que está Faltando
Com base nas regras e requisitos do exercício, eis os pontos que precisam ser corrigidos ou implementados:

## ajustar 

1. Parsing do Arquivo .cub --(Tales)
Atualmente, o código carrega um mapa hardcoded em get_map,
mas o exercício exige que o mapa seja lido de um arquivo .cub.
Deve-se implementar:
Leitura do arquivo .cub.
Parsing das configurações:
Texturas (NO, SO, WE, EA) com seus caminhos.
Cores para o chão (F) e teto (C).
Validação de erros no arquivo:
Mapas não fechados devem retornar um erro.
Identificadores inválidos ou ausentes devem retornar um erro.
Linhas vazias ou espaços dentro do mapa devem ser tratados corretamente.

2. Texturas
O programa deve renderizar texturas diferentes para cada face do muro (norte, sul, leste e oeste).
Deve-se:
Carregar texturas usando a MiniLibX (mlx_xpm_file_to_image).
Associar texturas às direções corretas (NO, SO, WE, EA).
Renderizar a textura correta com base na face do muro atingida pelo raycasting.

3. Cores do Chão e do Teto
O código deve permitir a configuração de cores diferentes para o chão e o teto (parsing dos identificadores F e C).
Deve-se implementar o preenchimento do chão e do teto com as cores apropriadas.

4. Gerenciamento de Eventos e Saída -- (sandro)
O código deve:
Fechar a janela e encerrar o programa ao pressionar ESC.
Fechar a janela e encerrar o programa ao clicar no botão de fechar (cruz vermelha).
Gerenciar redimensionamento/minimização da janela.
Deve-se garantir que toda a memória alocada seja liberada ao sair do programa.

5. Validação do Mapa --(sandro)
O mapa deve ser validado para garantir que:
Ele está completamente cercado por muros (1).
Existe exatamente uma posição inicial (N, S, E, W).
Não contém caracteres inválidos.
Deve-se verificar que espaços (0) são gerenciados corretamente no raycasting.

6. Leaks de Memória --Sandro
Verifique se toda memória alocada é liberada.
Use ferramentas como valgrind para identificar vazamentos de memória.
Garanta que free seja chamado para:
Texturas carregadas.
Mapas e matrizes alocados dinamicamente.

7. Respeitar a Norme da 42
Certifique-se de que:
Nenhuma função tenha mais de 25 linhas.
Não existam mais de 5 funções por arquivo.
Variáveis globais sejam evitadas.
Execute um teste de norminette para validar o código.

8. Erros de Configuração --(sandro)
Caso um erro ocorra no arquivo .cub ou no mapa, o programa deve sair com:
plaintext
Copiar código
Error
[Mensagem explicativa do erro]

## Lista de Tarefas
- Aqui está uma lista prática do que falta implementar:

- Parsing do arquivo .cub:

- Ler texturas (NO, SO, WE, EA).
- Ler cores (F, C).
- Ler e validar o mapa.
- Adicionar suporte a texturas:

- Carregar e renderizar texturas diferentes para cada face do muro.
- Adicionar cores para chão e teto.

- Implementar fechamento da janela e liberação de memória:

- Tratar eventos de ESC e botão de fechar.
- Garantir liberação de recursos.
- Validar o mapa:

- Verificar se o mapa está cercado.
- Verificar caracteres válidos e posição inicial.
- Testar leaks de memória com valgrind.

- Garantir conformidade com a Norme da 42:

- Testar com norminette.
- Recomendações
- Divida as funcionalidades em funções menores:

- Modularize o código para respeitar as restrições de linhas e número de funções.
- Teste em diferentes mapas:

- Crie mapas válidos e inválidos para testar sua implementação.
- Use ferramentas de depuração:

- Utilize valgrind para verificar leaks de memória.
- Teste o código com norminette.

```

```
## folta implementar
O que já está implementado:
Parser do Arquivo .cub:

A leitura do arquivo .cub já está parcialmente implementada.
As texturas são carregadas corretamente (NO, SO, WE, EA).
As cores do teto e do chão são processadas corretamente com validação.
O mapa é carregado linha por linha.
Estruturação do Jogo:

Estrutura básica do jogo (t_game, t_player, t_textures) está funcional.
Inicialização do jogador com ângulo e posição definidos.
Gerenciamento de eventos de teclado (key_press e key_release).
Raycasting:

O algoritmo de raycasting está implementado.
As texturas são aplicadas nas paredes com base na direção do raio.
Renderização:

O sistema de renderização para o mapa 2D (draw_map) e 3D (raycasting) está funcional.
Desenho de quadrados e linhas está implementado.
Gerenciamento de Memória:

Funções como free_map e free_split ajudam a liberar recursos alocados.
MiniLibX:

Uso correto de funções da MiniLibX para criar janelas e desenhar pixels.
Makefile:

Parece estar parcialmente funcional (embora não esteja incluso no código fornecido).
O que está faltando implementar ou melhorar:
Validação do Mapa:

Certificar-se de que o mapa está "fechado" (não pode haver espaços abertos).
Verificar se há apenas um ponto inicial (N, S, E, W).
Garantir que o mapa contém apenas os caracteres permitidos (0, 1, N, S, E, W).
Validar bordas do mapa (não podem ser espaços ou números inválidos).
Sugestão: Adicionar uma função validate_map para verificar essas condições.

Mensagem de Erro Melhorada:

Quando um erro ocorre no .cub, deve ser exibida a mensagem Error\n seguida de uma descrição do problema.
Gestão de Memória Completa:

Certificar-se de que todas as texturas e alocações dinâmicas são liberadas corretamente no encerramento do programa.
A função exit_program pode ser expandida para lidar com isso.
Interação com a Janela:

Implementar a funcionalidade para fechar a janela clicando no botão de fechar (gerenciamento de evento 17).
Melhorar a minimização/restauração da janela para evitar problemas gráficos.
Melhorias no Sistema de Colisão:

Certificar-se de que o jogador não consegue atravessar paredes, mesmo em cantos ou bordas.
Mapa de Depuração:

Melhorar a visualização do mapa 2D para depuração (cores diferentes para jogador, paredes, etc.).
Erros de Limites no Raycasting:

Garantir que os raios não ultrapassem os limites do mapa.
Makefile:

Adicionar uma regra bonus caso queira incluir funcionalidades extras.
Certificar-se de que ele compila corretamente sem relink.
Diretórios e Organização:

Separe as funções relacionadas ao jogador, mapa, renderização e utilitários em arquivos e diretórios distintos para melhorar a legibilidade e manutenção.
Testes e Validação:

Crie cenários de teste com diferentes mapas .cub para validar os casos de borda:
Mapas válidos.
Mapas com espaços não fechados.
Mapas sem texturas ou cores definidas.
Rotação de Câmera Suave:

As rotações da câmera podem ser suavizadas para melhorar a experiência do usuário.
Resolução Configurável:

Permitir a configuração de resolução via arquivo .cub.
Mensagens de Debug:

Adicionar uma flag de debug para habilitar/desabilitar mensagens de depuração.
Próximos Passos:
Implementar as validações do mapa:

Crie a função validate_map para assegurar que o mapa esteja correto.
Adicionar a função exit_program completa:

Libere todos os recursos corretamente ao sair do programa.
Testar intensivamente:

Utilize diferentes arquivos .cub para validar o comportamento do seu programa.
Aprimorar mensagens de erro:

Certifique-se de que todas as mensagens de erro sigam o formato Error\n e sejam claras.
Se precisar de a



## Use o gdb para Depuração
Para identificar exatamente onde o erro ocorre, use o gdb (GNU Debugger):
`gdb ./cub3d`

No gdb, inicie a execução com:
`run`

Quando o erro de segmentação ocorrer, o gdb exibirá a linha exata do código onde o problema aconteceu. Use o comando:
`backtrace`
Isso mostrará a pilha de chamadas para entender a origem do problema.