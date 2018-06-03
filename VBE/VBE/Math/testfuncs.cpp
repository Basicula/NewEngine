#include "testfuncs.h"

namespace Engine
{
	namespace Graph
	{
		float square(float x)
		{
			return x * x;
		}

		std::vector<Math::Vector2> lineInterpolation(const std::vector<Math::Vector2> &dots)
		{
			std::vector<Math::Vector2> result;

			for (int i = 0; i < dots.size(); i++)
			{
				result.push_back(dots[i]);
			}

			while (result.size() < 1000)
			{
				int n = result.size();
				for (int i = 1; i < n; i++)
				{
					double x, y;
					x = (result[i].x + result[i - 1].x) / 2;
					y = result[i - 1].y + (x - result[i - 1].x) / (result[i].x - result[i - 1].x)*(result[i].y - result[i - 1].y);
					result.push_back(Math::Vector2(x, y));
				}
				std::sort(result.begin(), result.end());
			}

			return result;
		}

		std::vector<Math::Vector2> polyInterpolation(const std::vector<Math::Vector2> &dots)
		{
			
			int n = dots.size();
			std::vector<std::vector<float>> matrix(n, std::vector<float>(n + 1));
			//fill matrix
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					matrix[i][j] = pow(dots[i].x, n - j - 1);
				}
				matrix[i][n] = dots[i].y;
			}

			for (int i = 0; i < n; i++)
			{
				float mainElem = matrix[i][i];
				for (int j = 0; j <= n; j++)
				{
					matrix[i][j] /= mainElem;
				}
				for (int j = 0; j < n; j++)
				{
					if (i == j) continue;
					float m = matrix[j][i];
					for (int k = 0; k <= n; k++)
					{
						matrix[j][k] -= matrix[i][k] * m;
					}
				}
			}
			//print
			/*for (int i = 0; i < n; i++)
			{
				for (int j = 0; j <= n; j++)
				{
					std::cout << matrix[i][j] << " ";
				}
				std::cout << std::endl;
			}*/
			std::vector<Math::Vector2> result;
			for (int i = 0; i < n; i++)
			{
				result.push_back(dots[i]);
			}
			std::sort(result.begin(), result.end());
			for (int i = 1; i < n; i++)
			{
				if (result[i - 1].dist(result[i]) < 1) continue;
				for (float x = result[i - 1].x + 0.1f; x < result[i].x; x += 0.1f)
				{
					float y = 0;
					for (int j = 0; j < n; j++)
					{
						y += matrix[j][n] * pow(x, n - 1 - j);
					}
					result.push_back(Math::Vector2(x, y));
				}
			}
			std::sort(result.begin(), result.end());
			/*for (int i = 0; i < n; i++)
			{
				std::cout << matrix[i][n] << "*x^" << n - 1 - i << ((i == n - 1) ? " = 0\n" : " + ");
			}*/
			return result;
		}

		std::vector<Math::Vector2> cubeSplainInterpolation(const std::vector<Math::Vector2> &dots)
		{
			int n = dots.size();
			std::vector<Math::Vector2> result;
			for (int i = 0; i < n; i++)
			{
				result.push_back(dots[i]);
			}
			std::vector<float> a(n), h(n), al(n), m(n), z(n), l(n), c(n), d(n), b(n);
			if (result.size() < 3) return polyInterpolation(result);

			a[n - 1] = result[n - 1].y;
			for (int i = 0; i < n - 1; i++)
			{
				a[i] = result[i].y;
				h[i] = result[i + 1].x - result[i].x;
			}

			for (int i = 1; i < n - 1; i++)
			{
				al[i] = (a[i + 1] - a[i]) * 3. / h[i] - (a[i] - a[i - 1]) * 3. / h[i - 1];
			}

			l[0] = 1;
			z[0] = 0;
			c[0] = 0;
			m[0] = 0;

			l[n - 1] = 1;
			z[n - 1] = 0;
			c[n - 1] = 0;

			for (int i = 1; i < n - 1; i++)
			{
				l[i] = 2 * (result[i + 1].x - result[i - 1].x) - h[i - 1] * m[i - 1];
				m[i] = h[i] / l[i];
				z[i] = (al[i] - h[i - 1] * z[i - 1]) / l[i];
			}

			for (int i = n - 2; i >= 0; i--)
			{
				c[i] = z[i] - m[i] * c[i + 1];
				b[i] = (a[i + 1] - a[i]) / h[i] - h[i] * (c[i + 1] + 2 * c[i]) / 3.;
				d[i] = (c[i + 1] - c[i]) / (3.*h[i]);
			}

			for (int i = 0; i < n - 1; i++)
			{
				float xi = result[i].x;
				float dx = std::max(0.1f, h[i] / 10);
				for (float x = xi + dx; x < result[i + 1].x; x += dx)
				{
					float y = a[i] + b[i] * (x - xi) + c[i] * pow(x - xi, 2) + d[i] * pow(x - xi, 3);
					result.push_back(Math::Vector2(x, y));
				}
			}
			sort(result.begin(), result.end());
			return result;
		}

		std::vector<Math::Vector2> interpolationLagrange(const std::vector<Math::Vector2>& dots)
		{
			std::vector<Math::Vector2> result;
			int n = dots.size();
			for (int i = 0; i < n; i++)
			{
				result.push_back(dots[i]);
			}
			for (int i = 0; i < n - 1; i++)
			{
				for (float x = result[i].x + 0.1f; x < result[i + 1].x; x += 0.1f)
				{
					float y = 0;
					for (int j = 0; j < n; j++)
					{
						float l = 1;
						for (int k = 0; k < n; k++)
						{
							if (k == j) continue;
							l *= (x - result[k].x) / (result[j].x - result[k].x);
						}
						y += result[j].y * l;
					}
					result.push_back(Math::Vector2(x, y));
				}
			}

			std::sort(result.begin(), result.end());
			return result;
		}

		/*std::vector<Math::Vector2> nInterpolation(const std::vector<Math::Vector2> &dots)
		{
			std::vector<Math::Vector2> result;
			for (int i = 0; i < dots.size(); i++)
			{
				result.push_back(dots[i]);
			}
			sort(result.begin(), result.end());
			for (float x = result[0].x + 0.1; x < result[dots.size() - 1].x; x += 0.1)
			{
				for (int i = 0; i < dots.size(); i++)
				{

				}
			}
		}*/
	}


}