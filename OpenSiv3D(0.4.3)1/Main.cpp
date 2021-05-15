# include <Siv3D.hpp>

std::pair<long double, long double> mandel(std::pair<long double, long double> p) {
    long double nr = 0;
    long double ni = 0;

    for (long long i = 0; i < 500; i++) {
        long double tmp = nr;
        nr = nr * nr - ni * ni;
        ni = 2 * tmp * ni;
        nr += p.first;
        ni += p.second;
    }

    return std::make_pair(nr,ni);
}

bool isMandel(long double x, long double y) {
    x /= 200;
    y /= 200;

    auto p = mandel(std::make_pair(x,y));
    long double dist = sqrt(p.first*p.first + p.second*p.second);

    if (dist <= 2) return true;
    else return false;
}

void Main()
{
    Scene::SetBackground(Palette::Black);
    int pointX = Cursor::Pos().x;
    int pointY = Cursor::Pos().y;
    int centerX = 400;
    int centerY = 300;

    while (System::Update())
    {
        if (MouseL.pressed()) Scene::SetBackground(Palette::Aqua);

        for (int i = 0; i <= 800; i++) {
            for (int j = 0; j <= 600; j++) {
                long double x = i - centerX;
                long double y = j - centerY;

                if (isMandel(x,y)) {
                    Circle(i, j, 1).draw();
                }
            }
        }
    }
}