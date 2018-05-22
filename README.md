# BitermTopicModel
BTM implementation for CSE291G


This repository contains a first approximation of the Biterm Topic Model that can be used to model short documents effectively.

The Biterm Topic Model assumes that there is a single topic distribution across the entire corpus, in contrast to LDA, which assumes that each document has a unique topic distribution. Another difference is that the Biterm Topic Model seeks to model pairs of co-occurring words (called a Biterm) instead of a single word.

Parameter Estimation is done using collapsed Gibbs Sampling. Gibbs sampling is a simple and widely applicable
Markov chain Monte Carlo algorithm. 

The code is implemented in basic Python 3.6, with no external packages. 

All code is contained in the BTM.ipynb notebook. 

I will update the documentation during this week.

Data
___________
Data has to be stored in the Data/ folder.
Currently, sample_data exists as a placeholder.
The data has to be preprocessed with each line representing a document, and each term in the document seperated by a space.

Output
____________
* 'model-final-theta.txt' Doc*Topic matrix
* 'model-final-phi.txt' Topic*Word matrix
* 'model-final-twords.txt' top 20 words of each topics
* 'model-final-wordmap.txt' word dictionary


Results
___________

Unfortunately, I was not able to get satisfactory results for the terms that belong to a particular topic. I have not been able to figure out the bug that is causing this.
