class Jar:
    def __init__(self, capacity=12):
        if capacity > 0:
            self._capacity = capacity
            self._size = 0

        else:
            raise ValueError

    def __str__(self):
        return "🍪" * self._size

    def deposit(self, n):
        if (n + self.size) <= self.capacity:
            self._size += n

        else:
            raise ValueError

    def withdraw(self, n):
        if n <= self.size:
            self._size -= n

        else:
            raise ValueError

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


jar = Jar()
print(str(jar.capacity))
print(str(jar))
jar.deposit(2)
print(str(jar))
jar.withdraw(1)
print(str(jar))
