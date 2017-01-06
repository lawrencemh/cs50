import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        # init and load positive words
        self.positive = []
        self.loadFileToList(positives, self.positive)
        
        # init and load negative words
        self.negative = []
        self.loadFileToList(negatives, self.negative)
        # TODO

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        if text.lower() in self.positive:
            return 1
        elif text.lower() in self.negative:
            return -1
        else:
            return 0

    # load file into list passed
    def loadFileToList(self, fileName, lst):
        with open(fileName) as f:
            for line in f:
                cLine = line.rstrip()
                if not cLine.startswith(";"):
                    lst.append(cLine)