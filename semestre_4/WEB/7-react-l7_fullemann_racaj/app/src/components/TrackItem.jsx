import { usePlayer } from "../context/PlayerContext";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { faPlay, faPlus } from "@fortawesome/free-solid-svg-icons";

export default function TrackItem({ track, index, trackList, showNumber = true }) {
  const { playTrack, addToQueue, currentIndex, trackList: currentTrackList } = usePlayer();
  
  const isCurrentTrack = currentTrackList === trackList && currentIndex === index;

  const handlePlay = (e) => {
    e.stopPropagation();
    playTrack(trackList, index);
  };

  const handleAddToQueue = (e) => {
    e.stopPropagation();
    addToQueue(track);
  };

  return (
    <div className={`track-item ${isCurrentTrack ? 'playing' : ''}`}>
      {showNumber && (
        <>
          <div className="track-number">{index + 1}</div>
          <div className="play-icon" onClick={handlePlay}>
            <FontAwesomeIcon icon={faPlay} />
          </div>
        </>
      )}
      
      <img
        src={track.album?.cover_small}
        alt={track.title}
        className="track-cover"
        onClick={handlePlay}
      />
      
      <div className="track-info" onClick={handlePlay}>
        <div className="track-title">{track.title}</div>
        <div className="track-artist">{track.artist?.name}</div>
      </div>
      
      
      <div className="track-actions">
        <button 
          className="control-btn"
          onClick={handleAddToQueue}
          title="Ajouter à la file d'attente"
        >
          <FontAwesomeIcon icon={faPlus} />
        </button>
      </div>
    </div>
  );
}