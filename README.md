# NBC
Naive Bayes Classifier on stackoverflow questions

Взаимодействие с программой:

	./prog learn --input <input file> --output <stats file>
	./prog classify --stats <stats file> --input <input file> --output <output file>
  
Формат входных файлов при обучении:

	<Количество строк в вопросе [n]>
	<Заголовок вопроса>
	<Текст вопроса [n строк]>
	<Тег 1>,<Тег 2>,...,<Тег m>
  
Формат входных файлов при запросах:

	<Количество строк в вопросе [n]>
	<Заголовок вопроса>
	<Текст вопроса [n строк]>
