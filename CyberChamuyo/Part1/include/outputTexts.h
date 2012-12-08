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
#define COMMAND_PRINT_WORD_RANKING "palabrasMasPopulares"
#endif /*COMMAND_PRINT_WORD_RANKING*/

#ifndef COMMAND_LOAD_DICTIONARY
#define COMMAND_LOAD_DICTIONARY "cargaDiccionario"
#endif /*COMMAND_LOAD_DICTIONARY*/

#ifndef COMMAND_LOAD_MEMORABLE_QUOTES
#define COMMAND_LOAD_MEMORABLE_QUOTES "cargaFrases"
#endif /*COMMAND_LOAD_MEMORABLE_QUOTES*/

#ifndef COMMAND_LOAD_INDEXES
#define COMMAND_LOAD_INDEXES "cargaIndices"
#endif	/*COMMAND_LOAD_INDEXES*/

#ifndef COMMAND_ERASE_PHRASE
#define COMMAND_ERASE_PHRASE "borrarFrase"
#endif

#ifndef COMMAND_BOOLEAN_SEARCH
#define COMMAND_BOOLEAN_SEARCH "busquedaBooleano"
#endif

#ifndef COMMAND_SIGNATURE_SEARCH
#define COMMAND_SIGNATURE_SEARCH "busquedaXFirma"
#endif

#ifndef COMMAND_ADD_PHRASE
#define COMMAND_ADD_PHRASE "agregarFrase"
#endif

#ifndef COMMAND_MODIFY_PHRASE
#define COMMAND_MODIFY_PHRASE "modificarFrase"
#endif

#ifndef COMMAND_INDEX_BY_BOOLEAN
#define COMMAND_INDEX_BY_BOOLEAN "indexarXBooleano"
#endif

#ifndef COMMAND_INDEX_BY_SIGNATURE
#define COMMAND_INDEX_BY_SIGNATURE "indexarXFirma"
#endif

#ifndef COMMAND_PRINT_HELP
#define COMMAND_PRINT_HELP "ayuda"
#endif /*COMMAND_PRINT_HELP*/

#ifndef ERROR_TEXT_INVALID_COMMAND
#define ERROR_TEXT_INVALID_COMMAND "Comando invalido: "
#endif /*ERROR_TEXT_INVALID_COMMAND*/

#ifndef ERROR_TEXT_INVALID_RANKING_SIZE
#define ERROR_TEXT_INVALID_RANKING_SIZE "La cantidad de palabras solicitadas debe ser mayor a 0."
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
#define HELP_TEXT_WORD_RANKING "	palabrasMasPopulares N: Muestra el ranking de las N palabras mas buscadas."
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

#ifndef HELP_TEXT_SIGNATURE_SEARCH
#define HELP_TEXT_SIGNATURE_SEARCH "	busquedaXFirma: Buscar frases por índice de porción de firmas."
#endif /*HELP_TEXT_CALLHELP*/

#ifndef HELP_TEXT_INDEX_BY_BOOLEAN
#define HELP_TEXT_INDEX_BY_BOOLEAN "	indexarXBooleano: Indexa por índice booleano."
#endif /*HELP_TEXT_CALLHELP*/

#ifndef HELP_TEXT_INDEX_BY_SIGNATURE
#define HELP_TEXT_INDEX_BY_SIGNATURE "	indexarXFirma: Indexa por índice de porciones de firma."
#endif /*HELP_TEXT_CALLHELP*/

#ifndef HELP_TEXT_EXIT
#define HELP_TEXT_EXIT "	salir: abandonar la aplicación."
#endif /*HELP_TEXT_EXIT*/

#ifndef HELP_TEXT_DICTIONARY_FILE_PATH
#define HELP_TEXT_DICTIONARY_FILE_PATH "Archivo de diccionario cargado: "
#endif /*HELP_TEXT_DICTIONARY_FILE_PATH*/

#ifndef HELP_TEXT_MEMORABLE_QUOTES_FILE_PATH
#define HELP_TEXT_MEMORABLE_QUOTES_FILE_PATH "Archivo de frases célebres cargado: "
#endif /*HELP_TEXT_MEMORABLE_QUOTES_FILE_PATH*/

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
#define TEXT_MOST_SEARCHED_WORDS_TITLE(N) "Ranking de las " + N + " palabras mas populares: "
#endif /*TEXT_MOST_SEARCHED_WORDS_TITLE*/

#ifndef TEXT_MOST_SEARCHED_WORDS_ITEM
#define TEXT_MOST_SEARCHED_WORDS_ITEM(itemNumber,word,times) itemNumber + ") " + word + " - " + times + " veces."
#endif /*TEXT_MOST_SEARCHED_WORDS_ITEM*/

#ifndef TEXT_NO_NOT_FOUND_WORDS
#define TEXT_NO_NOT_FOUND_WORDS "No hay palabras no encontradas."
#endif /*TEXT_NO_NOT_FOUND_WORDS*/

#ifndef TEXT_DICTIONARY
#define TEXT_DICTIONARY "diccionario"
#endif /*TEXT_DICTIONARY*/

#ifndef TEXT_MEMORABLE_QUOTES
#define TEXT_MEMORABLE_QUOTES "frases célebres"
#endif /*TEXT_MEMORABLE_QUOTES*/

#ifndef TEXT_NO_RESULTS_FOR_SEARCH
#define TEXT_NO_RESULTS_FOR_SEARCH "		No hubo coincidencias para esta busqueda"
#endif /*TEXT_NO_RESULTS_FOR_SEARCH*/

#ifndef EXECUTION_TIME_MSG
#define EXECUTION_TIME_MSG "	Tiempo de ejecucion: "
#endif /*EXECUTION_TIME_MSG*/

#ifndef SEARCH_TERM_LIST_MSG
#define SEARCH_TERM_LIST_MSG "		Terminos Buscados: "
#endif /*SEARCH_TERM_LIST_MSG*/

#ifndef ERROR_FILE_NOT_FOUND
#define ERROR_FILE_NOT_FOUND "No se pudo recuperar el archivo ubicado en: "
#endif /*ERROR_FILE_NOT_FOUND*/

#ifndef ERROR_STATUS_RETRIEVAL_FAILURE
#define ERROR_STATUS_RETRIEVAL_FAILURE "No se pudo recuperar el estado guardado del programa debido a los siguientes errores: "
#endif /*ERROR_STATUS_RETRIEVAL_FAILURE*/

#ifndef ERROR_CONFIG_DIRECTORY_NOT_FOUND
#define ERROR_CONFIG_DIRECTORY_NOT_FOUND "No ese encontró el directorio de archivos de configuracion."
#endif /*ERROR_CONFIG_DIRECTORY_NOT_FOUND*/

#ifndef ERROR_RETRIEVING_WORD_RANKING
#define ERROR_RETRIEVING_WORD_RANKING "Error al intentar reportar el ranking de palabras."
#endif /*ERROR_RETRIEVING_WORD_RANKING*/

#ifndef ERROR_COMMAND_PREREQUISITES
#define ERROR_COMMAND_PREREQUISITES "Antes de realizar la operación debe cargar los siguientes archivos: "
#endif /*ERROR_COMMAND_PREREQUISITES*/

#ifndef ERROR_COMMAND_SEARCH_PREREQUISITES
#define ERROR_COMMAND_SEARCH_PREREQUISITES "Para poder realizar búsquedas primero debe indexar"
#endif /*ERROR_COMMAND_SEARCH_PREREQUISITES*/

//#ifndef INEXISTANT_INPUT_DIRECTORY_ERROR
//#define INEXISTANT_INPUT_DIRECTORY_ERROR "ERROR: No existe directorio de archivos de entrada inputFiles"
//#endif
//
//#ifndef INEXISTANT_OR_BAD_STATUS_FILE_ERROR
//#define INEXISTANT_OR_BAD_STATUS_FILE_ERROR "ERROR: No existe archivo de configuracion statisticsManagerStatus"
//#endif
//
//#ifndef INEXISTANT_OR_BAD_PROPERTIES_FILE_ERROR
//#define INEXISTANT_OR_BAD_PROPERTIES_FILE_ERROR "ERROR: No existe archivo de propiedades statisticsManager.properties"
//#endif
//
//#ifndef INEXISTANT_OR_BAD_STOP_WORDS_FILE_ERROR
//#define INEXISTANT_OR_BAD_STOP_WORDS_FILE_ERROR "ERROR: No existe archivo de stopwords stop-words.txt"
//#endif
//
//#ifndef INEXISTANT_OR_BAD_CHAR_MAP_FILE_ERROR
//#define INEXISTANT_OR_BAD_CHAR_MAP_FILE_ERROR "ERROR: No existe archivo de configuracion de char map charMap"
//#endif
//
//#ifndef INEXISTANT_OR_BAD_DICTIONARY_FILE_ERROR
//#define INEXISTANT_OR_BAD_DICTIONARY_FILE_ERROR "ERROR: No existe archivo de entrada de diccionario dictionary.txt"
//#endif
//
//#ifndef INEXISTANT_OR_BAD_MEMORABLE_QUOTES_FILE_ERROR
//#define INEXISTANT_OR_BAD_MEMORABLE_QUOTES_FILE_ERROR "ERROR: No existe archivo de entrada de frases frases-celebres.txt"
//#endif

#endif /* OUTPUTTEXTS_H_ */
