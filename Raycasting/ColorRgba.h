#ifndef COLORRGBA_H
#define COLORRGBA_H


class ColorRgba
{
    public:

        explicit ColorRgba()
            :
              r(0.0f),
              g(0.0f),
              b(0.0f),
              a(1.0f)
        {}
        explicit ColorRgba(float r, float g, float b, float a = 1.0f)
            :
              r(r),
              g(g),
              b(b),
              a(a)
        {
            if (r < 0.0f) r = 0.0f;
            if (g < 0.0f) g = 0.0f;
            if (b < 0.0f) b = 0.0f;

            if (r > 1.0f) r = 1.0f;
            if (g > 1.0f) g = 1.0f;
            if (b > 1.0f) b = 1.0f;
        }


        float getRed() {return r;}
        float getGreen() {return g;}
        float getBlue() {return b;}
        float getAlpha() {return a;}

        void setRed(float red) {r = red; if (r < 0.0f) r = 0.0f; if (r > 1.0f) r = 1.0f;}
        void setGreen(float green) {g = green; if (g < 0.0f) g = 0.0f; if (g > 1.0f) g = 1.0f;}
        void setBlue(float blue) {b = blue; if (b < 0.0f) b = 0.0f; if (b > 1.0f) b = 1.0f;}
        void setAlpha(float alpha) {a = alpha; if (a < 0.0f) a = 0.0f; if (a > 1.0f) a = 1.0f;}

        void setColor(float red, float green, float blue)
        {
            r = red;
            g = green;
            b = blue;

            if (r < 0.0f) r = 0.0f;
            if (g < 0.0f) g = 0.0f;
            if (b < 0.0f) b = 0.0f;

            if (r > 1.0f) r = 1.0f;
            if (g > 1.0f) g = 1.0f;
            if (b > 1.0f) b = 1.0f;
        }

        void setColor(float red, float green, float blue, float alpha)
        {
            r = red;
            g = green;
            b = blue;
            a = alpha;

            if (r < 0.0f) r = 0.0f;
            if (g < 0.0f) g = 0.0f;
            if (b < 0.0f) b = 0.0f;
            if (a < 0.0f) a = 0.0f;

            if (r > 1.0f) r = 1.0f;
            if (g > 1.0f) g = 1.0f;
            if (b > 1.0f) b = 1.0f;
            if (a > 1.0f) a = 1.0f;
        }


        ColorRgba operator+ (const ColorRgba& otherColor) const
        {
            float red = r + otherColor.r;
            float green = g + otherColor.g;
            float blue = b + otherColor.b;

            if (1.0f < red)
            {
                red = 1.0f;
            }

            if (1.0f < green)
            {
                green = 1.0f;
            }

            if (1.0f < blue)
            {
                blue = 1.0f;
            }

            return ColorRgba(red, green, blue, a);
        }

        friend ColorRgba& operator+= (ColorRgba& thisColor, const ColorRgba& otherColor)
        {
            thisColor.r += otherColor.r;
            thisColor.g += otherColor.g;
            thisColor.b += otherColor.b;

            if (1.0f < thisColor.r)
            {
                thisColor.r = 1.0f;
            }

            if (1.0f < thisColor.g)
            {
                thisColor.g = 1.0f;
            }

            if (1.0f < thisColor.b)
            {
                thisColor.b = 1.0f;
            }

            return thisColor;
        }

        ColorRgba operator- (const ColorRgba& otherColor) const
        {
            float red = r - otherColor.r;
            float green = g - otherColor.g;
            float blue = b - otherColor.b;

            if (0.0f > red)
            {
                red = 0.0f;
            }

            if (0.0f > green)
            {
                green = 0.0f;
            }

            if (0.0f > blue)
            {
                blue = 0.0f;
            }

            return ColorRgba(red, green, blue, a);
        }

        friend ColorRgba& operator-= (ColorRgba& thisColor, const ColorRgba& otherColor)
        {
            thisColor.r -= otherColor.r;
            thisColor.g -= otherColor.g;
            thisColor.b -= otherColor.b;

            if (0.0f > thisColor.r)
            {
                thisColor.r = 0.0f;
            }

            if (0.0f > thisColor.g)
            {
                thisColor.g = 0.0f;
            }

            if (0.0f > thisColor.b)
            {
                thisColor.b = 0.0f;
            }

            return thisColor;
        }

        ColorRgba operator* (float scalar)
        {
            return ColorRgba(r * scalar, g * scalar, b * scalar, a);
        }

        ColorRgba& operator*= (float scalar)
        {
            r *= scalar;
            g *= scalar;
            b *= scalar;

            return *this;
        }

        ColorRgba operator/ (float scalar)
        {
            if (0.0f != scalar)
            {
                return ColorRgba(r / scalar, g / scalar, b / scalar, a);
            }

            return ColorRgba(r, g, b);
        }

        ColorRgba& operator/= (float scalar)
        {
            if (0.0f != scalar)
            {
                r /= scalar;
                g /= scalar;
                b /= scalar;
            }

            return *this;
        }

        ColorRgba& operator= (const ColorRgba& otherColor)
        {
            if (this != &otherColor)
            {
                r = otherColor.r;
                g = otherColor.g;
                b = otherColor.b;
                a = otherColor.a;
            }

            return *this;
        }

        bool operator!= (const ColorRgba& otherColor)
        {
            if (this != &otherColor)
            {
                if ((r == otherColor.r) && (g == otherColor.g) && (b == otherColor.b) && (a == otherColor.a))
                {
                    return false;
                }
            }

            return true;
        }

        bool operator== (const ColorRgba& otherColor)
        {
            if (this != &otherColor)
            {
                if ((r == otherColor.r) && (g == otherColor.g) && (b == otherColor.b) && (a == otherColor.a))
                {
                    return true;
                }
            }

            return false;
        }


    private:

        float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
};


#endif // COLORRGBA_H
