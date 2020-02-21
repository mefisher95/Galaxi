#include "Highscores.h"

void read(std::vector < int > & score)
{
    
    std::ifstream in_file;
    in_file.open("Highscores.txt");
    for (int i = 0; i < score.size(); ++i)
    {
        int n;
        in_file >> n;
        //std::cout << n << std::endl;
        score[i] = n;
    }
    in_file.close();
}

void write(std::vector < int > & score)
{
    std::ofstream out_file;
    
    if (HUD::score_ > score[score.size() - 1])
        score[score.size() - 1] = HUD::score_;
    HUD::score_ = 0;
    
    for (int i = 0; i < score.size(); ++i)
    {
        for (int j = i + 1; j < score.size(); ++j)
        {
            if (score[i] < score[j])
            {
                int z = score[i];
                score[i] = score[j];
                score[j] = z;
            }
        }
    }
    out_file.open("Highscores.txt");
    for (int i = 0; i < score.size(); ++i)
    {
        out_file << score[i] << std::endl;
    }
    out_file.close();
}
