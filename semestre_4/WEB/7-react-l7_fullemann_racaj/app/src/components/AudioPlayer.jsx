import { usePlayer } from "../context/PlayerContext";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import {
  faPlay,
  faPause,
  faStepBackward,
  faStepForward,
  faVolumeUp,
} from "@fortawesome/free-solid-svg-icons";

export default function AudioPlayer() {
  const {
    audioRef,
    trackList,
    currentIndex,
    prev,
    next,
    togglePlay,
    isPlaying,
    currentTime,
    duration,
    seek,
    volume,
    setVolumeLevel,
  } = usePlayer();

  const current = trackList[currentIndex];

  const formatTime = (seconds) => {
    if (isNaN(seconds)) return "0:00";
    const mins = Math.floor(seconds / 60);
    const secs = Math.floor(seconds % 60);
    return `${mins}:${secs.toString().padStart(2, '0')}`;
  };

  const handleProgressClick = (e) => {
    const progressBar = e.currentTarget;
    const clickX = e.nativeEvent.offsetX;
    const width = progressBar.offsetWidth;
    const newTime = (clickX / width) * duration;
    seek(newTime);
  };

  const handleVolumeClick = (e) => {
    const volumeBar = e.currentTarget;
    const clickX = e.nativeEvent.offsetX;
    const width = volumeBar.offsetWidth;
    const newVolume = clickX / width;
    setVolumeLevel(newVolume);
  };

  if (!current) {
    return null;
  }

  const progressPercentage = duration ? (currentTime / duration) * 100 : 0;
  const volumePercentage = volume * 100;

  return (
    <div className="player-bar">
      {/* Informations de la piste */}
      <div className="player-track-info">
        <img
          src={current.album?.cover_small}
          alt={current.title}
          className="player-track-cover"
        />
        <div className="player-track-details">
          <div className="player-track-title">{current.title}</div>
          <div className="player-track-artist">{current.artist?.name}</div>
        </div>
      </div>

      {/* Contrôles de lecture */}
      <div className="player-controls">
        <div className="controls">
          <button
            onClick={prev}
            aria-label="Piste précédente"
            className="control-btn"
          >
            <FontAwesomeIcon icon={faStepBackward} />
          </button>
          
          <button
            onClick={togglePlay}
            aria-label={isPlaying ? "Pause" : "Lecture"}
            className="control-btn play-btn"
          >
            <FontAwesomeIcon icon={isPlaying ? faPause : faPlay} />
          </button>
          
          <button
            onClick={next}
            aria-label="Piste suivante"
            className="control-btn"
          >
            <FontAwesomeIcon icon={faStepForward} />
          </button>
        </div>

        {/* Barre de progression */}
        <div className="progress-container">
          <span className="time-display">{formatTime(currentTime)}</span>
          <div className="progress-bar" onClick={handleProgressClick}>
            <div 
              className="progress-fill" 
              style={{ width: `${progressPercentage}%` }}
            />
          </div>
          <span className="time-display">{formatTime(duration)}</span>
        </div>
      </div>

      {/* Contrôles supplémentaires */}
      <div className="player-extras">
        <div className="volume-control">
          <button className="control-btn">
            <FontAwesomeIcon icon={faVolumeUp} />
          </button>
          <div className="volume-bar" onClick={handleVolumeClick}>
            <div 
              className="volume-fill" 
              style={{ width: `${volumePercentage}%` }}
            />
          </div>
        </div>
      </div>

      <audio ref={audioRef} src={current.preview} />
    </div>
  );
}