### Trabalho 2
> Implemente um simulador de um sistema de arquivos, utilizando a linguagem C, que possua as seguintes características:

1. [1,0] Simular um disco com 256 setores de 512 bytes. Considere que os 10 primeiros setores são ocupados pelo setor de boot, sistema de arquivos e o diretório raiz, ficando os demais setores disponíveis para dados do usuário.

- [x] Criar 256 setores com 512 bytes cada
- [ ] Ocupar os 10 primeiros setores

2. [1,0] O simulador deve permitir a alocação de arquivos de forma não contígua. Sugere-se **usar uma tabela de alocação de blocos** e um mapa de bits para gerenciar o espaço livre (a mesma estrutura pode ou não ser aproveitada para ambos os propósitos).

- [x] Criar a tabela de ocupação de blocos / mapa de bits

3. [0,8] O simulador deve permitir a criação de diretórios e subdiretórios com um comando criad até o mínimo de 8 níveis. Cada diretório pode conter vários subdiretórios. Cada diretório/subdiretório ocupa um setor do disco.
Sugestão de sintaxe: criad caminho\nome_do_diretorio

- [ ] Permitir criar diretórios; Até 8 níveis
- [ ] CRIAD: Criar diretório

4. [0,8] O simulador deve permitir a criação de arquivos dentro dos diretórios e subdiretórios com um comando criaa. Cada diretório pode conter diversos arquivos. Ao criar o arquivo o tamanho do mesmo deve ser especificado e devem ser alocados setores no disco de acordo com seu tamanho. Nomes de arquivos precisam ser únicos dentro de um diretório/subdiretório.
Sugestão de sintaxe: criaa caminho\nome_do_arquivo tamanho

- [ ] Permitir criar arquivos com tamanho pré definidos
- [ ] Não pode haver nomes duplicados dentro do diretório
- [ ] CRIAA: Criar arquivo (parâmetro: tamanho)
- [ ] Salvar data e hora da criação

5. [0,8] O simulador deve permitir a exclusão de diretórios utilizando um comando removed. O simulador não deve permitir a exclusão de diretórios que não estejam vazios.

- [ ] Permitir exclusão de diretório (somente vazios)
- [ ] REMOVED: Exclui um diretório

6. [0,8] O simulador deve permitir a exclusão de arquivos utilizando um comando removea. 

- [ ] Permitir exclusão de um arquivo
- [ ] REMOVEA: Exclui um arquivo

7. [1,0] O simulador deve oferecer um comando verd que exibe os arquivos e subdiretórios do diretório indicado como parâmetro. Na listagem, os diretórios devem conter uma indicação de que são diretórios e os arquivos devem conter tamanho, além de data e hora de criação. No final da listagem deve aparecer o total de arquivos e diretórios, o total do tamanho dos arquivos e a quantidade de espaço livre no disco. Lembre-se que o espaço vazio dos setores utilizados não pode ser utilizado por outros arquivos ou diretórios, portanto não devem entrar na conta do espaço livre.
Sugestão de sintaxe: verd caminho

- [ ] Listar arquivos e diretórios
- [ ] Para arquivos: tamanho, data e hora de criação
- [ ] Mostrar o total de arquivos e diretórios
- [ ] Mostrar soma do tamanho dos arquivos
- [ ] Mostrar quantidade de espaço livre
- [ ] VERD: Listagem da pasta

8. [1,0] O simulador deve oferecer um comando verset que exibe quais são os setores ocupados por determinado arquivo.
Sugestão de sintaxe: verset caminho\nome_do_arquivo

- [ ] VERSET: Mostrar setores ocupados pelo arquivo

9. [1,0] O simulador deve oferecer um comando mapa que mostre graficamente quais são os setores ocupados e quais são os setores livres.

- [x] Exibir o mapa de bits (já implementado no item 2)
- [x] LISTASET --> showset

10. [1,0] O simulador deve oferecer um comando árvore que mostra graficamente a árvore de diretórios do sistema de arquivos.

- [ ] Exibir a árvore de diretórios (já implementada no item 3)

11. [0,4] O simulador deve oferecer um comando ajuda que pode ser usado para mostrar quais são os comandos disponíveis no sistema.

- [ ] HELP:

12. [0,4] O simulador deve fornecer um comando sair que pode ser usado para encerrar o simulador.

- [ ] EXIT:

Observações:
O trabalho pode ser feito individualmente, em dupla ou em trio.

Os nomes de comandos são apenas sugestão e podem ser substituídos a gosto. Utilize estruturas para representar os setores, armazenando nelas os metadados do diretório ou arquivo correspondente, além dos ponteiros que forem necessários.

Para simplificar a alocação de arquivos, você pode considerar que todo o espaço de um setor utilizado por um arquivo será usado por dados do usuário, ou seja, o espaço ocupado por metadados e ponteiros não precisa ser computado.

Não é necessário ficar limitado aos requisitos ou ao modelo, use sua criatividade para criar um simulador ainda melhor.

Todos os membros do grupo deverão ter domínio suficiente para responder qualquer questão sobre o código-fonte e o comportamento do programa.