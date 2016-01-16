#include "bayesianclassifier.h"

#include "patrec_types.h"

using namespace cv;
using namespace std;

BayesianClassifier::BayesianClassifier(QString className)
{
    mClassName = className;
}

cv::Size BayesianClassifier::size() const
{
    return mSize;
}

void BayesianClassifier::setSize(const cv::Size &size)
{
    mSize = size;
}

int BayesianClassifier::type() const
{
    return mType;
}

void BayesianClassifier::setType(int type)
{
    mType = type;
}

void BayesianClassifier::performCalculations(pr::training_vector tv)
{
    qDebug() << "Size of training vector " << tv.size() <<  "x"
             << tv.at(0).size();


    //building a Mat object from vector pointer
    cv::Mat mat(tv.size(), tv.at(0).size(), CV_8UC1);

    int rows = mat.rows;
    int cols = mat.cols;

    for (int r = 0; r < rows; ++r) {

        uchar *pInput = mat.ptr<uchar>(r);

        for (int c = 0; c < cols; ++c) {
            *pInput = tv.at(r)[c];
            ++pInput;
        }
    }

    mData = mat;

    //showing raw data
    pr::showSingleImage("mData", mData);


    cv::Mat covar, mean;

    cv::calcCovarMatrix(mData, covar, mean, CV_COVAR_NORMAL | CV_COVAR_ROWS, CV_32SC1);

    mCovariance = covar;
    mMean = mean;

    qDebug() << "Size of MEAN matrix " << mMean.rows <<  "x"
             << mMean.cols;

    qDebug() << "Size of COVARIANCE matrix " << mCovariance.rows <<  "x"
             << mCovariance.cols;


    Mat m(mean);
    m.convertTo(m, CV_8UC1);
    pr::double_vector v;

    for(int i = 0; i < m.rows * m.cols; i++) {
        v.push_back(mean.at<uchar>(0,i));
    }

    pr::showSingleImage("COVAR", mCovariance);
    pr::convertVectorToImageAndShow(mSize, mType, &v, "MEAN VECTOR");

    StatisticsCalculator sc;
    sc.setPosVector(&tv);
    sc.setNegVector(&tv);

    pr::convertVectorToImageAndShow(mSize, mType, sc.positiveMeanVector(),
                                    "MEAN VECTOR - OLD METHOD");

}


