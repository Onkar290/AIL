
movie('The Shawshank Redemption', drama, happy).
movie('Inception', sci_fi, happy).
movie('The Dark Knight', action, sad).
movie('La La Land', musical, happy).
movie('The Silence of the Lambs', thriller, sad).
movie('Jurassic Park', adventure, happy).
movie('The Godfather', crime, sad).
movie('Eternal Sunshine of the Spotless Mind', sci_fi, sad).
movie('Gladiator', action, happy).
movie('Forrest Gump', drama, happy).
movie('The Matrix', sci_fi, happy).
movie('Pulp Fiction', crime, sad).
movie('Amélie', romance, happy).
movie('The Lord of the Rings: The Fellowship of the Ring', fantasy, happy).
movie('The Revenant', adventure, sad).
movie('Avatar', sci_fi, happy).
movie('The Social Network', drama, neutral).

recommend_movie(Mood, Genre, RecommendedMovie) :-
    findall(Movie, (movie(Movie, MovieGenre, MovieMood), matching_parameters(Mood, Genre, MovieGenre, MovieMood)), MatchingMovies),
    (MatchingMovies = [] ->
        findall(Movie, movie(Movie, MovieGenre, _), GenreMovies)
    ;
        GenreMovies = MatchingMovies
    ),
    random_member(RecommendedMovie, GenreMovies).

matching_parameters(Mood, Genre, MovieGenre, MovieMood) :-
    (Mood = MovieMood; Mood = 'any'),
    (Genre = MovieGenre; Genre = 'any').

start :-
    write('How are you feeling today (\nhappy\nsad\nneutral\nany\n'),
    read(Mood),
    write('What genre do you prefer (\ndrama\nsci_fi\naction\nmusical\nthriller\nadventure\ncrime\nromance\nfantasy\nany\n '),
    read(Genre),
    recommend_movie(Mood,Genre, RecommendedMovie),
    nl, write('Based on your preferences, we recommend: '), write(RecommendedMovie), nl,
    fail. 

