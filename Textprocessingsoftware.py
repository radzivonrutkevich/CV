import nltk
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.tokenize import RegexpTokenizer
from nltk.probability import FreqDist





print ("********************************************************************")
print ("*                                                                  *")
print ("*                   СИСТЕМА ОПРЕДЕЛЕНИЯ ТЕМАТИКИ                   *")
print ("*                    НЕСТРУКТУРИРОВАННОГО ТЕКСТА                   *")
print ("*                                                                  *")
print ("*                       (с) Руткевич Р. 2020                       *")
print ("********************************************************************")
print ("База входных документов:  dbIn")
print ("База выходных документов: dbOut")
print ("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")


dbIn = open('D:\Text Analyse\infodocs.txt', 'r',encoding='utf-8') # dbIn
text = dbIn.read()
inputtext = text
dbIn.close()
print ("Агент aIn: документ * " + dbIn.name + " * считан из dbIn")
print ("Начало парсинга текста")
regexpression = RegexpTokenizer(r'\w+')
stop_words = set(stopwords.words("russian"))
text = text.lower() # приводим текст к нижнему регистру
text_tokenized = regexpression.tokenize(text)
text = [i for i in text_tokenized if not i in stop_words] # удаление stop-words из текста
top_words = FreqDist(text)
top_words = top_words.most_common(5)
first_element , third_elemenet = top_words[0] # разбиваем самую частую пару на слово и количество его повторений
second_element , forth_elemenet = top_words[1] # разбиваем вторую по частоте пару на слово и количество его повторений
print ("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
print('Название документа: ' + dbIn.name)
print('Тематика: ' + first_element + " " + second_element)
print('Ключевые слова: ' + str(top_words))
print ("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
print('Исходный текст: ')
print(inputtext)





