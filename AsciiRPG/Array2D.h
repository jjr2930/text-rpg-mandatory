#ifndef ARRAY_2D_H
#define ARRAY_2D_H


template <typename T>
class Array2D
{
public:
    Array2D(int width, int height)
        : width(width), height(height)
    {
        data = new T[width * height];
        for (int i = 0; i < width * height; ++i)
        {
            data[i] = T();
        }
    }

    ~Array2D()
    {
        delete[] data;
    }

    T& operator()(int x, int y)
    {
        return data[y * width + x];
    }

    const T& operator()(int x, int y) const
    {
        return data[y * width + x];
    }

    int GetWidth() const
    {
        return width;
    }

    int GetHeight() const
    {
        return height;
    }

private:
    T* data;
    int width;
    int height;
};

#endif // !ARRAY_2D_H