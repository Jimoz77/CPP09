#include "BitcoinExchange.hpp"
#include <cfloat>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

bool isValidDate(const std::string& date)
{
    // 1. Vérifier la taille exacte
    if (date.length() != 10)
        return false;

    // 2. Vérifier la position des tirets et des chiffres
    for (int i = 0; i < 10; ++i)
	{
        if (i == 4 || i == 7)
		{
            if (date[i] != '-') 
                return false;
        }
		else
		{
            if (!std::isdigit(date[i])) 
                return false;
        }
    }

    // 3. Extraire l'année, le mois et le jour en entiers
    // substr(position_depart, longueur)
    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    // 4. Vérifier la logique du calendrier
    if (year < 0 || month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    // Gestion des mois de 30 jours (Avril, Juin, Septembre, Novembre)
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

    // Gestion de Février et des années bissextiles
    if (month == 2)
	{
        bool isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (isLeap && day > 29)
			return false;
        if (!isLeap && day > 28)
			return false;
    }

    return true;
}



const std::map<std::string, float> inputData::mapper(std::string file)
{
	std::ifstream fd(file.c_str());
	if(!fd.is_open())
		throw WInputFile();
	std::string line;
	std::string date;
	std::string sep;
	std::string valuestr;
	float rate;
	std::map<std::string, float> map;
	std::getline(fd,line);
	while(std::getline(fd,date, ','))
	{
		if(std::getline(fd, valuestr))
		{
			rate = std::atof(valuestr.c_str());
			map.insert(std::make_pair(date, rate));
		}
	}
	return map;

}

std::map<std::string, float>::const_iterator findClosestDate(std::string& targetDate, const std::map<std::string, float>& database) {
    
    // On utilise lower_bound pour trouver le premier élément >= targetDate
    std::map<std::string, float>::const_iterator it = database.lower_bound(targetDate);

    // Cas 1 : On a trouvé la date exacte !
    if (it != database.end() && it->first == targetDate) {
        return it; 
    }

    // Cas 2 : La date demandée est plus ancienne que la TOUTE PREMIÈRE date de notre base.
    // Dans ce cas, il n'y a pas de date inférieure possible[cite: 168, 169].
    if (it == database.begin()) {
        return database.end(); // On retourne end() pour signifier une erreur / "non trouvé"
    }

    // Cas 3 : La date n'existe pas exactement, mais il y a des dates antérieures.
    // lower_bound nous a donné la date directement SUPÉRIEURE. 
    // On recule donc d'un élément pour avoir la date INFÉRIEURE la plus proche[cite: 168, 169].
    --it;
    
    return it;
}

inputData::inputData(std::string input)
{
    // 1. Ouverture du fichier d'entrée
    std::ifstream inputFile(input.c_str());
    if(!inputFile.is_open())
        throw WInputFile();

    std::string line;
    std::string date;
    std::string separator;
    float value;

    // 2. Chargement de la base de données CSV
    const std::map<std::string, float> btcDb = mapper("../cpp_09/data.csv");

    // 3. On ignore la première ligne du fichier .txt (l'en-tête "date | value")
    std::getline(inputFile, line);

    // 4. On lit le reste du fichier ligne par ligne
    while(std::getline(inputFile, line))
    {
        std::istringstream parsedString(line);

        // Si on arrive à extraire les 3 éléments (date, séparateur, valeur)
        if(parsedString >> date >> separator >> value)
        {
            // Vérification du séparateur
            if(separator == "|")
            {
                // Vérification du format de la date AVANT de chercher dans la map
                if(!isValidDate(date))
                {
                    std::cerr << "Error: bad input => " << line << std::endl;
                }
                else
                {
                    // La date est au bon format, on cherche la date la plus proche
                    std::map<std::string, float>::const_iterator closestValue = findClosestDate(date, btcDb);
                    
                    if(closestValue == btcDb.end())
                    {
                        std::cerr << "Error: no valid date found for: " << date << std::endl;
                    }
                    else if (value >= 0 && value <= 1000)
                    {
                        float rate = closestValue->second;
                        float result = value * rate;
                        std::cout << date << " => " << value << " = " << result << std::endl;
                    }
                    else if(value < 0)
                    {
                        std::cerr << "Error: not a positive number." << std::endl;
                    }
                    else
                    {
                        std::cerr << "Error: too large a number." << std::endl;
                    }
                }
            }
            else
            {
                std::cerr << "Error: bad input => " << line << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: bad input => " << line << std::endl;
        }
    }
}
inputData::inputData(const inputData &other)
{
	(void)other;
}

inputData& inputData::operator=(const inputData &other)
{
	(void)other;
	return (*this);
}

inputData::~inputData()
{
}


