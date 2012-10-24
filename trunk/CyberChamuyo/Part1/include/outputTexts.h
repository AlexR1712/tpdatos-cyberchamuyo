#ifndef OUTPUTTEXTS_H_
#define OUTPUTTEXTS_H_

// Header para incluir los textos a usar en la aplicación.

#ifndef COMMAND_PRINT_AVG_WORDS_PER_QUOTE
#define COMMAND_PRINT_AVG_WORDS_PER_QUOTE "palabrasPromedio"
#endif /*COMMAND_PRINT_AVG_WORDS_PER_QUOTE*/

#ifndef COMMAND_PRINT_AVG_FAILURES
#define COMMAND_PRINT_AVG_FAILURES "fallosPromedio"
#endif /*COMMAND_PRINT_AVG_FAILURES*/

#ifndef COMMAND_PRINT_NOT_FOUND_WORDS
#define COMMAND_PRINT_NOT_FOUND_WORDS "palabrasNoEncontradas"
#endif /*COMMAND_PRINT_NOT_FOUND_WORDS*/

#ifndef COMMAND_PRINT_WORD_RANKING
#define COMMAND_PRINT_WORD_RANKING "palabrasMasBuscadas"
#endif /*COMMAND_PRINT_WORD_RANKING*/

#ifndef COMMAND_LOAD_DICTIONARY
#define COMMAND_LOAD_DICTIONARY "cargaDiccionario"
#endif /*COMMAND_LOAD_DICTIONARY*/

#ifndef COMMAND_LOAD_MEMORABLE_QUOTES
#define COMMAND_LOAD_MEMORABLE_QUOTES "cargaFrases"
#endif /*COMMAND_LOAD_MEMORABLE_QUOTES*/

#ifndef COMMAND_PRINT_HELP
#define COMMAND_PRINT_HELP "ayuda"
#endif /*COMMAND_PRINT_HELP*/

#ifndef ERROR_TEXT_INVALID_COMMAND
#define ERROR_TEXT_INVALID_COMMAND "Comando invalido"
#endif /*ERROR_TEXT_INVALID_COMMAND*/

#ifndef ERROR_TEXT_INVALID_RANKING_SIZE
#define ERROR_TEXT_INVALID_RANKING_SIZE "La cantidad de palabras del ranking debe ser mayor a 0."
#endif /*ERROR_TEXT_INVALID_RANKING_SIZE*/

#ifndef HELP_TITLE
#define HELP_TITLE "Ayuda:"
#endif /*HELP_TITLE*/

#ifndef HELP_TEXT_AVG_WORDS_PER_QUOTE
#define HELP_TEXT_AVG_WORDS_PER_QUOTE "	palabrasPromedio: Muestra la cantidad de palabras promedio por frase."
#endif /*HELP_TEXT_AVG_WORDS_PER_QUOTE*/

#ifndef HELP_TEXT_AVG_FAILURES
#define HELP_TEXT_AVG_FAILURES "	fallosPromedio: Muestra la cantidad de fallos promedio."
#endif /*HELP_TEXT_AVG_FAILURES*/

#ifndef HELP_TEXT_NOT_FOUND_WORDS
#define HELP_TEXT_NOT_FOUND_WORDS "	palabrasNoEncontradas: Muestra el listado de palabras no encontradas."
#endif /*HELP_TEXT_NOT_FOUND_WORDS*/

#ifndef HELP_TEXT_WORD_RANKING
#define HELP_TEXT_WORD_RANKING "	palabrasMasBuscadas N: Muestra el ranking de las N palabras mas buscadas."
#endif /*HELP_TEXT_WORD_RANKING*/

#ifndef HELP_TEXT_LOAD_DICTIONARY
#define HELP_TEXT_LOAD_DICTIONARY "	cargaDiccionario path: Cargar un nuevo diccionario ubicado en la ruta espedificada."
#endif /*HELP_TEXT_LOAD_DICTIONARY*/

#ifndef HELP_TEXT_LOAD_MEMORABLE_QUOTES
#define HELP_TEXT_LOAD_MEMORABLE_QUOTES "	cargaFrases path: Cargar un nuevo archivo de frases ubicado en la ruta especificada."
#endif /*HELP_TEXT_LOAD_MEMORABLE_QUOTES*/

#ifndef HELP_TEXT_CALLHELP
#define HELP_TEXT_CALLHELP "	ayuda: reimprimir esta ayuda."
#endif /*HELP_TEXT_CALLHELP*/

#ifndef HELP_TEXT_EXIT
#define HELP_TEXT_EXIT "	salir: abandonar la aplicación."
#endif /*HELP_TEXT_EXIT*/

#ifndef TEXT_AVG_WORDS_PER_QUOTE
#define TEXT_AVG_WORDS_PER_QUOTE "Cantidad de terminos promedio por frase: "
#endif /*TEXT_AVG_WORDS_PER_QUOTE*/

#ifndef TEXT_AVG_FAILURES
#define TEXT_AVG_FAILURES "Tasa de fallos de terminos: "
#endif /*TEXT_AVG_FAILURES*/

#ifndef TEXT_NOT_FOUND_WORDS
#define TEXT_NOT_FOUND_WORDS "Terminos no encontrados: "
#endif /*TEXT_NOT_FOUND_WORDS*/

#ifndef TEXT_MOST_SEARCHED_WORDS_TITLE
#define TEXT_MOST_SEARCHED_WORDS_TITLE(N) "Ranking de las " + N + " palabras mas buscadas: "
#endif /*TEXT_MOST_SEARCHED_WORDS_TITLE*/

#ifndef TEXT_MOST_SEARCHED_WORDS_ITEM
#define TEXT_MOST_SEARCHED_WORDS_ITEM(itemNumber,word,times) itemNumber + ") " + word + " - " + times + " veces."
#endif /*TEXT_MOST_SEARCHED_WORDS_ITEM*/

#endif /* OUTPUTTEXTS_H_ */
