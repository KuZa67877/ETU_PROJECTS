from sklearn.datasets import load_wine
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier


def loadData():
    wine = load_wine()

    X_train, X_test, y_train, y_test = train_test_split(
        wine.data[:, :2], wine.target, test_size=0.2, random_state=42)

    return X_train, X_test, y_train, y_test


def distance(X_train, y_train):
    clf = KNeighborsClassifier(n_neighbors=15, weights='distance')

    clf.fit(X_train, y_train)
    return clf


def predict(clf, X_test):
    return clf.predict(X_test)


def estimate(y_pred, y_test):
    return (y_pred == y_test).mean()
