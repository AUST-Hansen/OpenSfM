#pragma once

#include <sfm/types.h>

#include <map>
#include <vector>
#include <unordered_map>

class TracksManager {
 public:
  std::vector<ShotId> GetShotIds();
  std::vector<TrackId> GetTrackIds();

  cv::KeyPoint GetObservation(const ShotId& shot, const TrackId& point);

  // Not sure if we use that
  std::map<TrackId, cv::KeyPoint> GetObservationsOfShot(const ShotId& shot);

  // For point triangulation
  std::map<ShotId, cv::KeyPoint> GetObservationsOfPoint(const TrackId& point);

  // For shot resection
  std::map<TrackId, cv::KeyPoint> GetObservationsOfPointsAtShot(
      const std::vector<TrackId>& points, const ShotId& shot);

  // For pair bootstrapping
  using ShotIdPair = std::pair<ShotId, ShotId>;
  using KeyPointPair = std::pair<cv::KeyPoint, cv::KeyPoint>;
  std::map<ShotIdPair, KeyPointPair> GetAllCommonObservations(
      const ShotId& shot1, const ShotId& shot2);

  // I/O
  static TracksManager InstanciateFromFile();
  static bool WriteToFile();

  private:
  std::unordered_map< ShotId, std::unordered_map<TrackId, cv::KeyPoint> > tracks_per_shot_;
  std::unordered_map< TrackId, std::unordered_map<ShotId, cv::KeyPoint> > shot_per_tracks_;
};