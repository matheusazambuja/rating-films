# movie-lens-20M
Trabalho final da cadeira de Classificação e Pesquisa de Dados 2019/2. Trabalho foi
realizado em dupla.

Objetivo: aplicar as diversas técnicas vista em aula para explorar o dataset MovieLens 20M. Nele contém tags e avaliações e tags (em texto-livre) do serviço. São 20,000,263 avaliações (notas de 1 a 5) e 465,564 aplicações de tags (jazz, hero, animation, dark hero, etc) em 27,278 filmes.

Arquivos: formato .csv
movie.csv: movieid,title,genres
tag.csv: userid,movieid,tag,timestamp
rating.csv: userid,movieid,rating,timestamp
Esses arquivos podem ser baixados em: https://www.kaggle.com/grouplens/movielens-20m-dataset

Tarefas: Construção e inicialização das estruturas de dados, e modo console.                                                               
Estrutura de dados: Árvore Trie, Tabela Hash e AVL.                                                                                       

Pesquisas:
movie <title or prefix>: retorna a lista de filmes com esse prefixo e para cada filme o genero, avaliaçaão média e número de avaliações. 
(implementada somente para confirmar se o filme esta no dataset, sem pesquisa).

user <useID>: retorna a lista de filmes avaliações pelo usuários e para cada filme mostrar a nota dada pelo usuário, a média global e a contagem de avaliações.

top<N> '<genre>' - retorna os N filmes com melhores notas de um dado gênero com no mínimo 1000 avaliações.

tags <list of tags> - retorna para cada lista de tags dada, a pesquisa deve apresentar a lista de filmes que estão associados a essas tags.
ex: tags 'hero' 'marvel'

(erro: filmes com diferentes tags sao retornados da pesquisa)
