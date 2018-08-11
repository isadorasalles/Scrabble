# Scrabble

Aqui temos um código de uma palavra cruzada com as seguintes regras:

Inicio do Jogo:
1. Cada jogar inicia com 7 letras aleatórias. Na sua vez, o jogador vai tentar
colocar todas as suas letras no tabuleiro, ligadas a uma ou mais palavras
existentes, e de forma a que resultem novas palavras válidas. O jogador
soma os pontos das letras de todas as palavras que formou, incluindo das
letras já colocadas, possivelmente multiplicados pelos bônus marcados no
tabuleiro.
2. Cada letra tem uma determinada pontuação, que é tanto mais alta quanto
mais rara seja essa letra na língua em que o jogo está. Por exemplo, em
português A e O valem 1 ponto cada, enquanto a letra X vale 8 pontos;
3. Após a sua tentativa, o jogador tira aleatoriamente de um saco tantas
letras quantas necessárias para ficar novamente com sete. O jogo termina
quando se esgotarem as letras do saco. Ganha quem tiver marcado mais
pontos desde o início do jogo.

Peças:

A edição do jogo em português contém 118 peças.

0 pontos: Peças brancas ×3

1 ponto: A x14, E x11, I x10, O x10, S x8, U x7, M x6, R x6, T x5

2 pontos: D x5, L x5, C x4, P x4

3 pontos: N x4, B x3

4 pontos: F x2, G x2, H x2, V x2

5 pontos: J x2

6 pontos: Q x1

8 pontos: X x1, Z x1

Regras do Jogo:

• Troca de pedras: Todos os jogadores podem usar a sua vez para trocar
uma ou todas as pedras que têm no seu suporte. Se o jogador usar a sua
vez para trocar pedras, perde a vez. A escolha pela troca de peças é feita
no início da jogada, ou se formam palavras ou se trocam as pedras.

• Fim da jogada: Os jogadores, ao fim das rodadas, terão que ter sempre 07
pedras consigo (exceto quando não tiverem peças suficientes no saco), ou
seja, no final de cada jogada o jogador “compra” o número de peças que
utilizou na sua jogada.

• Fim do jogo: O jogo termina se: Todas as pedras forem retiradas do
saquinho e um dos jogadores já não tiver pedras em seu suporte; Não for
mais possível formar nenhuma palavra Todos os jogadores passarem a vez
duas rodadas seguidas

• No fim do jogo, da pontuação geral de cada jogador deve ser subtraído
o valor das suas letras que ficaram no seu suporte. Se um dos jogadores
usou todas as letras, ele deverá somar à sua pontuação o valor das letras
que restaram no suporte dos outros jogadores. Ex: O jogador 1 ficou com
as letras X e E no seu suporte. Da sua pontuação final devem ser retirados
9 pontos. O jogador que colocou todas as suas letras em jogo e terminou
sem nenhuma no suporte, somará esse 9 pontos a sua pontuação final.

Representando o Jogo com Estruturas de Dados
1. O Tabuleiro foi implementado como uma matriz 15 por 15;
2. O saco de letras foi implementado como uma lista com inserção de letras de forma aleatória inicialmente.
3. As 7 letras do jogador foram representadas como um array do tipo player (uma struct criada no código)
4. O dicionário de palavras válidas foi implementado usando uma trie.
